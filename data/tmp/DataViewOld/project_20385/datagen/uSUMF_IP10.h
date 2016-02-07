QList<QVariant> tmp;
// Данные ГО
tmp.clear();
tmp<<f.getNumber()<<f.getNumObj()<<f.getTypeIstInfo()<<f.getPrOpozn();
tableNumbers.append(0);
data.append(tmp);

//     
tmp.clear();
tmp<<f.getD()<<f.getP();
tableNumbers.append(1);
data.append(tmp);
