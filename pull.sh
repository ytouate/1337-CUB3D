read m
if [[ -z $m ]]
then
    echo "No"
else
    git add *
    git commit -m "$m"
    git pull
fi