QList<QVariant> tmp;
// Рекомендации по маневрированию
tmp.clear();
tmp<<f.getid_rec()<<f.gettak_zad()<<f.getzad_rec()<<f.getnum_cel_GAK()<<f.getnum_cel_kor()<<f.gettip_cel_kor();
tableNumbers.append(0);
data.append(tmp);

//  
tmp.clear();
tmp<<f.getdatetime_rec()<<f.getdatetime_rec_rez()<<f.getraz_pov()<<f.getgal_man();
tableNumbers.append(1);
data.append(tmp);

// Первый галс
tmp.clear();
tmp<<f.getkurs_gals1()<<f.getskor_gals1()<<f.getdlit_gals1();
tableNumbers.append(2);
data.append(tmp);

// Второй галс
tmp.clear();
tmp<<f.getkurs_gals2()<<f.getskor_gals2()<<f.getdlit_gals2();
tableNumbers.append(3);
data.append(tmp);

// Третий галс
tmp.clear();
tmp<<f.getkurs_gals3()<<f.getskor_gals3()<<f.getdlit_gals3();
tableNumbers.append(4);
data.append(tmp);

// Четвертый галс
tmp.clear();
tmp<<f.getkurs_gals4()<<f.getskor_gals4()<<f.getdlit_gals4();
tableNumbers.append(5);
data.append(tmp);

// Пятый галс
tmp.clear();
tmp<<f.getkurs_gals5()<<f.getskor_dals5()<<f.getdlit_gals5();
tableNumbers.append(6);
data.append(tmp);
