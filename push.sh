message=$1
if [[ -z $message ]]
then
    echo "Insert The Commit Message"
else
    git add *
    git commit -m "$message"
    git push
fi