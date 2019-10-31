for b in $(cat chr.txt)
do
mkdir ${b}.dir 
awk '{if($3=="$b") print $0}' STEP3.region_call.txt> ${b}.dir/sam.txt                
cp bpr_pull_0525.o ${b}.dir/bpr_pull_0525.o
cd ${b}.dir
./bpr_pull_0525.o
wait
mv bpr_output.txt ${b}.txt
done
