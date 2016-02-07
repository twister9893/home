QList<QVariant> tmp;
// Информация о состоянии и режимах работы БИУС
tmp.clear();
tmp<<f.getreg_rab()<<f.getsost_sist()<<f.getreg_fun_PLO();
tableNumbers.append(0);
data.append(tmp);
