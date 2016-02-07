QList<QVariant> tmp;
// Состав комплексированного объекта
tmp.clear();
tmp<<f.getTypeIstInfo()<<f.getPrVklIskl()<<f.getNumObj()<<f.getTypeSyst();
tableNumbers.append(0);
data.append(tmp);
