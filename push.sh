echo "Insert the commit Message"
read message

if [[ -z $message ]]
then
    echo "Insert The Commit Message"
else
    git add .
    git commit -m $message
    git push
fi