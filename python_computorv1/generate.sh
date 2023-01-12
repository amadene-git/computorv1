a=1

while [ "$a" -eq "1" ]
do
    python main.py "$(python test.py 2)" > tmp;
    cat tmp | grep "Polynomial degree: 2" > /dev/null;
    a=$?
    if [ "$a" -eq "1" ]
    then
        cat tmp | grep "Polynomial degree: 1" > /dev/null;
        a=$?
    fi
done

cat tmp
rm -rf tmp