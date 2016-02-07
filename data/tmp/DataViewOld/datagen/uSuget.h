QList<QVariant> tmp;
// Средняя скорость ветра
tmp.clear();
tmp<<f.getV2()<<f.getVt2()<<f.getV10()<<f.getVt10();
tableNumbers.append(0);
data.append(tmp);

// Среднее направление
tmp.clear();
tmp<<f.getK2()<<f.getKt2()<<f.getK10()<<f.getKt10();
tableNumbers.append(1);
data.append(tmp);

// Остальные
tmp.clear();
tmp<<f.getDavl()<<f.getVlg()<<f.getT()<<f.getVdm()<<f.getObl();
tableNumbers.append(2);
data.append(tmp);

// Тестовые данные
tmp.clear();
tmp<<f.getObl();
tableNumbers.append(3);
data.append(tmp);

// Еще Одни тестовые данные
tmp.clear();
tmp;
tableNumbers.append(4);
data.append(tmp);
