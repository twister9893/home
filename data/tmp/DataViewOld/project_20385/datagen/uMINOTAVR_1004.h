QList<QVariant> tmp;
// Рекомендации по буксировке
tmp.clear();
tmp<<f.getid_rec()<<f.gettak_zad()<<f.getnum_cel_GAK()<<f.getnum_cel_kor();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.gettip_cel_kor()<<f.getrec_glub()<<f.getrec_dlin()<<f.getrec_skor();
tableNumbers.append(1);
data.append(tmp);
