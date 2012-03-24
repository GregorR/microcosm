#define _POSIX_SOURCE /* for strtok_r */
#define _SVID_SOURCE /* for strdup */

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

static const char whitespace[] = " \t\r\n";
static int ccArgc;
static char **ccArgv;

static char *getCommand(char **buf)
{
    /* get a command out of this buffer */
    int depth = 0;
    char *cmd = *buf;
    if (!(*cmd)) return NULL;

    /* look 'til EOL unless in depth */
    for (; **buf; (*buf)++) {
        switch (**buf) {
            case '(':
            case '[':
            case '{':
                depth++;
                break;

            case ')':
            case ']':
            case '}':
                depth--;
                break;

            case '\n':
                if (depth == 0) {
                    /* we're done! */
                    **buf = '\0';
                    (*buf)++;
                    return cmd;
                }
        }
    }

    /* found the end of input */
    return cmd;
}

static char *skipWhitespace(char *buf)
{
    while (strchr(whitespace, *buf)) buf++;
    return buf;
}

static char *trimWhitespace(char *buf)
{
    int i;
    buf = skipWhitespace(buf);
    i = strlen(buf);
    for (i--; i >= 0 && strchr(whitespace, buf[i]); i--) buf[i] = '\0';
    return buf;
}

static void handle_include(char **sp) {
    char *cmd = strtok_r(NULL, "", sp);
    printf("#include %s\n", cmd);
}

static void fixupStructName(char *structNm)
{
    int i;

    /* remove anything that's not a "good" filename */
    for (i = 0; structNm[i]; i++) {
        if (!isalnum(structNm[i])) {
            structNm[i] = '_';
        }
    }
}

static char *getDeclaration(char **sp)
{
    char *decl = strtok_r(NULL, ";", sp);
    if (!decl) return NULL;
    decl = trimWhitespace(decl);
    if (*decl == '}') return NULL;
    return decl;
}

static char *getDeclName(char *decl, int *isArray)
{
    int i;
    *isArray = 0;

    /* if it is an array, skip to the beginning of the [] syntax */
    i = strlen(decl) - 1;
    if (decl[i] == ']') {
        *isArray = 1;
        for (i--; i >= 0 && decl[i] != '['; i--); /* FIXME: much better detection needed */
        if (i >= 0) decl[i] = '\0';
    }

    /* we could have just added some whitespace (between the name and []) */
    decl = trimWhitespace(decl);
    i = strlen(decl) - 1;

    /* now skip back to the beginning of the name */
    for (; i >= 0 && (isalnum(decl[i]) || decl[i] == '_'); i--);
    return decl + i + 1;
}

static void handleDeclaration(struct Buffer_char *str, struct Buffer_char *h2g,
    struct Buffer_char *g2h, char *structNm, char *pureStructNm, char *decl)
{
    char *name;
    int isArray;

    /* our "type" handling is extremely primitive, to say the least, we only
     * care about the name and our special tags, if present */
    EXPAND_BUFFER_TO(*str, strlen(decl)+2);
    str->bufused += sprintf(BUFFER_END(*str), "%s;\n", decl);

    /* FIXME: flag support, array support */

    /* get just the name part */
    name = getDeclName(decl, &isArray);

    if (isArray) {
        EXPAND_BUFFER_TO(*h2g, strlen(name)*6 + 106);
        h2g->bufused += sprintf(BUFFER_END(*h2g),
            "memcpy(guest->%s, host->%s, ((sizeof(guest->%s)<sizeof(host->%s))?sizeof(guest->%s):sizeof(host->%s)));\n",
            name, name, name, name, name, name);
        EXPAND_BUFFER_TO(*g2h, strlen(name)*6 + 106);
        g2h->bufused += sprintf(BUFFER_END(*g2h),
            "memcpy(host->%s, guest->%s, ((sizeof(guest->%s)<sizeof(host->%s))?sizeof(guest->%s):sizeof(host->%s)));\n",
            name, name, name, name, name, name);

    } else {
        EXPAND_BUFFER_TO(*h2g, strlen(name)*2 + 24);
        h2g->bufused += sprintf(BUFFER_END(*h2g),
            "guest->%s = host->%s;\n",
            name, name);
        EXPAND_BUFFER_TO(*g2h, strlen(name)*2 + 24);
        g2h->bufused += sprintf(BUFFER_END(*g2h),
            "host->%s = guest->%s;\n",
            name, name);

    }
}

static void handle_struct(char **sp)
{
    /* three buffers: one for the struct we're defining through, one for h2g,
     * one for g2h */
    struct Buffer_char str, h2g, g2h;

    char *decl;

    /* the struct name is everything up to a { */
    char *structNm = strtok_r(NULL, "{", sp);
    char *pureStructNm;

    INIT_BUFFER(str);
    INIT_BUFFER(h2g);
    INIT_BUFFER(g2h);

    /* fixup the struct name */
    structNm = trimWhitespace(structNm);
    SF(pureStructNm, strdup, NULL, (structNm));
    fixupStructName(structNm);

    /* and begin the buffers */
    EXPAND_BUFFER_TO(str, strlen(structNm) + 13);
    str.bufused += sprintf(BUFFER_END(str), "struct MC_%s {\n", structNm);
    EXPAND_BUFFER_TO(h2g, strlen(structNm)*2 + strlen(pureStructNm) + 99);
    h2g.bufused += sprintf(BUFFER_END(h2g),
        "static void MC_%s_h2g(struct MC_%s *guest, const %s *host) {\n"
        "memset(guest, 0, sizeof(*guest));\n",
        structNm, structNm, pureStructNm);
    EXPAND_BUFFER_TO(g2h, strlen(structNm)*2 + strlen(pureStructNm) + 97);
    g2h.bufused += sprintf(BUFFER_END(g2h),
        "static void MC_%s_g2h(%s *host, const struct MC_%s *guest) {\n"
        "memset(host, 0, sizeof(*host));\n",
        structNm, pureStructNm, structNm);

    /* get each element out of the struct */
    while (decl = getDeclaration(sp)) {
        handleDeclaration(&str, &h2g, &g2h, structNm, pureStructNm, decl);
    }

    /* finish the buffers and write it all out */
    EXPAND_BUFFER_TO(str, 3);
    str.bufused += sprintf(BUFFER_END(str), "};\n");
    EXPAND_BUFFER_TO(h2g, 2);
    h2g.bufused += sprintf(BUFFER_END(h2g), "}\n");
    EXPAND_BUFFER_TO(g2h, 2);
    g2h.bufused += sprintf(BUFFER_END(g2h), "}\n");

    printf("%.*s%.*s%.*s",
        str.bufused, str.buf,
        h2g.bufused, h2g.buf,
        g2h.bufused, g2h.buf);

    FREE_BUFFER(g2h);
    FREE_BUFFER(h2g);
    FREE_BUFFER(str);
}

static void handleCommand(char *cmd)
{
    char *saveptr, *oper;

    oper = strtok_r(cmd, whitespace, &saveptr);

#define OPER(nm) if (!strcmp(oper, #nm)) handle_ ## nm(&saveptr)
    if (oper[0] == '#') {
        /* preprocessor junk, skip it */
        return;
    }
    else OPER(include);
    else OPER(struct);
    else {
        fprintf(stderr, "Unrecognized operation \"%s\"!\n", oper);
        exit(1);
    }
}

int main(int argc, char **argv)
{
    struct Buffer_char buf;
    char *cmd, *cur;

    ccArgc = argc - 1;
    ccArgv = argv + 1;

    /* read in the input */
    INIT_BUFFER(buf);
    READ_FILE_BUFFER(buf, stdin);
    *BUFFER_END(buf) = '\0';

    /* generic header */
    printf("/* THIS FILE IS GENERATED */\n#include <string.h>\n#include <sys/types.h>\n");

    /* go command-by-command */
    cur = buf.buf;
    while (cmd = getCommand(&cur)) {
        /* skip obnoxious whitespace */
        cmd = skipWhitespace(cmd);

        /* and handle it */
        handleCommand(cmd);
    }

    return 0;
}
