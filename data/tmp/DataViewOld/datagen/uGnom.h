QList<QVariant> tmp;
// Дата
tmp.clear();
tmp<<f.getYearDec()<<f.getYearEd()<<f.getMonDec()<<f.getMonEd()<<f.getDayDec()<<f.getDayEd();
tableNumbers.append(0);
data.append(tmp);

// Время
tmp.clear();
tmp<<f.getTUTCDec()<<f.getTUTCEd()<<f.getTMskDec()<<f.getTMskEd()<<f.getTPoDec()<<f.getTPoEd();
tableNumbers.append(1);
data.append(tmp);

// Секунды
tmp.clear();
tmp<<f.getMinDec()<<f.getMinEd()<<f.getSecDec()<<f.getSecEd()<<f.getDoliSecDec()<<f.getDoliSecSot()<<f.getDoliSecT();
tableNumbers.append(2);
data.append(tmp);
