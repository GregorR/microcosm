USEDIR=`dirname "$0"`
for i in `$USEDIR/paths.sh`
do
    PATH="$i:$PATH"
done
export PATH
unset USEDIR
