if [ $# -ne 1 ]
then
echo "WRONG! Usage: ./compile.sh run or ./compile.sh clean"
else
if [ $1 = run ]
then
cd assembler
make
cd ..
cd processor
make debug=1
cd ..
elif [ $1 = clean ]
then
cd assembler
make clean
cd ..
cd processor
make clean
cd ..
else
echo "WRONG! Usage: ./compile.sh run or ./compile.sh clean"
fi
fi
