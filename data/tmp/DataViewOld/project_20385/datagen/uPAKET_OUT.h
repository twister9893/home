QList<QVariant> tmp;
// Состояние МТПК "Пакет"
tmp.clear();
tmp<<f.getCupr()<<f.getRr()<<f.getCispr()<<f.getBoPB()<<f.getBoLB();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getpu_bzn1214()<<f.getpu_bzs1214()<<f.getCst();
tableNumbers.append(1);
data.append(tmp);

// Данные об одной - четырех торпедах, классифицированных изделием "Пакет - А"
tmp.clear();
tmp<<f.getNgas14()<<f.getKgas14()<<f.getDgas14()<<f.getVir14()<<f.getTgl14()<<f.getTogs14();
tableNumbers.append(2);
data.append(tmp);

// Данные о применении изделия "МТПК Пакет"
tmp.clear();
tmp<<f.getRz()<<f.getKst()<<f.getVpor()<<f.getNtext();
tableNumbers.append(3);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getRkurs()<<f.getRspeed()<<f.getNplo()<<f.getCy();
tableNumbers.append(4);
data.append(tmp);

// Готовность стрельбовых данных (СД) ПЛО:
tmp.clear();
tmp<<f.getKst_got1()<<f.getKst_got2()<<f.getKst_got3()<<f.getKst_got4()<<f.getKst_got5()<<f.getKst_got6();
tableNumbers.append(5);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getnc()<<f.getKzalp()<<f.getdelt14()<<f.getKgotcd14();
tableNumbers.append(6);
data.append(tmp);
