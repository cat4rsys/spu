if [ $# -ne 1 ]
then
echo "WRONG! Usage: ./compile.sh (path to file)"
else
pathasm=$1
endin=${pathasm: -4}
if [ $endin != ".asm" ]
then
echo "You should specify the path to .asm file"
else
assembler/assemble $pathasm
pathobj=${pathasm/".asm"/".obj"}
processor/spu $pathobj
rm $pathobj
fi
fi
