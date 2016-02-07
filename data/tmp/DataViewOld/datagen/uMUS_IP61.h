QList<QVariant> tmp;
//  
tmp.clear();
tmp<<f.getKolFor()<<f.getKolObsl()<<f.getSostA190()<<f.getSostAK630_P()<<f.getSostAK630_L();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getSostBlockA190()<<f.getSostBlockAK630_P()<<f.getSostBlockAK630_L()<<f.getTipA190()<<f.getKolA190_1tip()<<f.getKolA190_2tip()<<f.getKolA190_3tip();
tableNumbers.append(1);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getUGNA190()<<f.getUVNA190()<<f.getUGNAK630_P()<<f.getUVNAK630_P()<<f.getUGNAK630_L()<<f.getUVNAK630_L();
tableNumbers.append(2);
data.append(tmp);
