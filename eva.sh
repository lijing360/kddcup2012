awk -f mae.awk res.txt
sort -nk3 res.txt | awk -f auc.awk
