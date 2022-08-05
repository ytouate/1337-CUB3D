read m
if [[ -z $m ]]
then
    echo "Insert a Commit Message"
else
    git add *
    git commit -m "$m"
    git pull
fi