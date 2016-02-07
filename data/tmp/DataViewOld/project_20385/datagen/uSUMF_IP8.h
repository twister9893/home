QList<QVariant> tmp;
// Доклад о выполении команды управления по объекту
tmp.clear();
tmp<<f.getNumber()<<f.getNumObj()<<f.getTypeIstInfo()<<f.getPriorSopr()<<f.getRez();
tableNumbers.append(0);
data.append(tmp);
