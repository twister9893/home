QList<QVariant> tmp;
//  
tmp.clear();
tmp<<f.getIdIzd()<<f.getIsprA190()<<f.getIsprAK630_P()<<f.getIsprAK630_L();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getGotA190()<<f.getGotAK630_P()<<f.getGotAK630_L()<<f.getNalOb_Sigma()<<f.getNalOb_RLK();
tableNumbers.append(1);
data.append(tmp);
