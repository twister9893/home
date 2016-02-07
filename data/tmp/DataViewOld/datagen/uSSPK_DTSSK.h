QList<QVariant> tmp;
// Параметры корабля
tmp.clear();
tmp<<f.getX()<<f.getY()<<f.getZ();
tableNumbers.append(0);
data.append(tmp);

// Составляющие путевой скорости по осям
tmp.clear();
tmp<<f.getVx()<<f.getVy()<<f.getVz();
tableNumbers.append(1);
data.append(tmp);

// широта/долгота корабля
tmp.clear();
tmp<<f.getF()<<f.geta()<<f.getL()<<f.getb();
tableNumbers.append(2);
data.append(tmp);

//               
tmp.clear();
tmp<<f.getHk()<<f.getVf()<<f.getVl()<<f.getx();
tableNumbers.append(3);
data.append(tmp);
