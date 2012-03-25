awk -f mae.awk $1
sort -nk3 $1 | awk -f auc.awk
