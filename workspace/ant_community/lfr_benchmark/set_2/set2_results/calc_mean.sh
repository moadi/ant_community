#!/bin/bash

e=0.1
f=0.2
g=0.3
h=0.4
i=0.5
j=0.6
k=0.7
l=0.8

file=$e\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file

file=$f\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file


file=$g\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file


file=$h\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file


file=$i\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file


file=$j\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file


file=$k\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file


file=$l\_data

fileName=1000_s_$file

#echo $file
read -ra values <<< `java Statistics $fileName`

a=${values[0]}

b=${values[1]}

c=${values[2]}

d=${values[3]}

printf -v mean "%.4f\n" "$a"
printf -v std_dev "%.4f\n" "$b"
printf -v cv "%.4f\n" "$c"
printf -v max "%.4f\n" "$d"

#sed -i '1s/^/# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max \n/" 1000_b_0.6_data

echo "# Mean = $mean, std dev = $std_dev, CV = $cv, Best = $max" | cat - 1000_s_$file > temp && mv temp 1000_s_$file






