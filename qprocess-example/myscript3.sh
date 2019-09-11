echo "type yes to try:"
read n
if [[ $n == "yes" ]];
then
    echo "success"
    exit 0;
else
    echo "failed"
    exit 1;
fi
