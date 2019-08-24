echo "enter your name:"
read n
if [[ ! -z "$n" ]];
then
    echo "success"
    exit 0;
else
    echo "failed"
    exit 1;
fi
