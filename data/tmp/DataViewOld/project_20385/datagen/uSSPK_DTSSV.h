QList<QVariant> tmp;
// Параметры вертолета
tmp.clear();
tmp<<f.getA()<<f.getDz();
tableNumbers.append(0);
data.append(tmp);

//    
tmp.clear();
tmp<<f.getX()<<f.getY()<<f.getWx();
tableNumbers.append(1);
data.append(tmp);

//             
tmp.clear();
tmp<<f.getKist()<<f.getU()<<f.getKu();
tableNumbers.append(2);
data.append(tmp);

//            
tmp.clear();
tmp<<f.getHb()<<f.getHist()<<f.getPt();
tableNumbers.append(3);
data.append(tmp);

//             
tmp.clear();
tmp<<f.getKWIT()<<f.getCC1()<<f.getCC2();
tableNumbers.append(4);
data.append(tmp);
