# Identification and Characterization of Occult Human-specific LINE-1 Insertions using Long-read Sequencing Technology
## BLASR
```
#for PacBio raw read
blasr ./SRR_hdf5/SRR.fofn hs37d5.fa -sa hs37d5.blasr.sa -clipping soft -sam -out SRR.sam

#for alignment of error corrected reads
blasr ./correctedReads.fasta region.fa --sam --clipping soft --out region.sam 
```

## Canu
```
canu useGrid=false -correct -d ./region/canu.0510 -p region.date genomeSize=60k -pacbio-raw ./region/output.fastq
```

## MELT
```
#for NA12878 Illumina platimun data
java -jar ./MELTv2.0.2/MELT.jar Single -l NA12878.bam  -w /workdir -t ./MELTv2.0.2/me_refs/1KGP_Hg19/LINE1_MELT.zip -h hs37d5.fa -n ./MELTv2.0.2/add_bed_files/1KGP_Hg19/hg19.genes.bed -c 49 -b hs37d5

#for single-cell experiment (scWGS59)
java -jar ./MELTv2.0.2/MELT.jar Single -l 82759.bam -w /workdir -t ./MELTv2.0.2/me_refs/1KGP_Hg19/LINE1_MELT.zip -h hs37d5.fa -n ./MELTv2.0.2/add_bed_files/1KGP_Hg19/hg19.genes.bed -b hs37d5 -c 21
```

## jellyFish
```
#for establishing 26mers index
jellyfish count -m 26 -s 5G -t 10 -o jf.index.26kmers <(zcat ./ERR194147_1.fastq.gz) <(zcat ./ERR194147_2.fastq.gz) <(zcat ./ERR194147.fastq.gz)


#for kmer counting
jellyfish query jf.index.26kmers 26mer.list.in.reads >> count.26.NA12878.0824.txt
```

## PALMER
```
#Frozen vesion for the project at https://github.com/mills-lab/PALMER/releases/tag/V1.3.0
PALMER --input ./alignment_hs37d5/NA12878.washu.alignment_hs37d5.${i}.bam --workdir ./chr${i}.line/ --ref_ver GRCh37 --output NA12878.chr${i} --chr chr${i} --ref_fa ./reference/hs37d5/hs37d5.fa --type LINE
```

## Pipelines for 3' targeted capture LINE-1 Illumina Miseq sequencing data
```
#Step1: Trimming (require the input.fastq that is going to be trimmed)
g++ trimmer.cpp -o trimmer.o
./trimmer.o

#Step2: bwa-mem alignment
bwa mem -t 15 hs37d5.fa R1_001.fastq R2_trimmed_gDNA.fastq > bwa.NA12878.trimmed.300.sam
samtools view -Sb bwa.NA12878.trimmed.300.sam  > bwa.NA12878.trimmed.300.bam
samtools sort -T /tmp/bwa.NA12878.trimmed.300.sorted -o bwa.NA12878.trimmed.300.sorted.bam bwa.NA12878.trimmed.300.bam
samtools index bwa.NA12878.trimmed.300.sorted.bam

#Step3: PCR duplicates removal and region calling
samtools rmdup bwa.NA12878.trimmed.300.sorted.bam bwa.NA12878.trimmed.300.sorted.rmdup.bam
samtools view bwa.NA12878.trimmed.300.sorted.rmdup.bam | awk '{print $1,$2,$3,$4,$5,$6}' > STEP3.region_call.txt
g++ bpr_pull_0525.cpp -o bpr_pull_0525.o
./bash.calling.region.sh
```
