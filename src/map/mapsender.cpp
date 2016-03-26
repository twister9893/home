#include "system.h"

int main(int argc,char* argv[])
{
    assert(sys.Init(argc,argv));

	MSG6_OurShip ourShip;
	MSG1_Target msg1;
	MSG100_RashParam params;

	ourShip.setT(1);
	ourShip.setFgrad(54.724423);
	ourShip.setLgrad(19.808993);
	ourShip.setKgrad(270);
	ourShip.setVuz(18);
	ourShip.save();

	msg1.setSourNum(OtogSour_NADV,1);
	msg1.setT(1);
	msg1.setTargetType(TargetType_NADV);
	msg1.setPgrad(270);
	msg1.setDml(10.8);
	msg1.setKgrad(90);
	msg1.setVuz(18);
	msg1.save();

	msg1.setSourNum(OtogSour_NADV,2);
	msg1.setT(1);
	msg1.setTargetType(TargetType_NADV);
	msg1.setGO(GosOp_OUR);
	msg1.setPgrad(289);
	msg1.setDml(9.2);
	msg1.setKgrad(90);
	msg1.setVuz(15);
	msg1.save();

	msg1.setSourNum(OtogSour_PODV,3);
	msg1.setT(1);
	msg1.setTargetType(TargetType_PODV);
	msg1.setGO(GosOp_ENEMY);
	msg1.setPgrad(0);
	msg1.setDml(7.3);
	msg1.setKgrad(0);
	msg1.setVuz(5);
	msg1.save();
    
//     int i=1000;
//     double D = 7.3;
//     while(i--)
//     {
//         sleep(1);
//         D += 0.1;
//         msg1.setDml(D);
//         msg1.save();
//     }


    if(argc > 1 && argv[1][0] == 'G')
    {
//        printf("mapsender.cpp OUR SHIP: %.2f  %.2f\n", sys.ourShip.getFgrad(), sys.ourShip.getLgrad());
//        MSG251_GraphElem gelem(47,3);
//        gelem.setColor(200,1,0,100);
//        gelem.setColorContour(0,20,20,100);
//        gelem.setLineWidth(2);
//  //      gelem.setKeyOtog(0);
//        gelem.setKeyOtog(MSG1_Target(OtogSour_PODV,3).getKey());
//        gelem.setParasector(std::pair<double,double>(0.0,0.0), 0.0, 2.0, 3.0, 90.0, CoordType_XY);
//        //gelem.setSector(std::pair<double,double>(54.724423, 19.808993), 50.0, 3.0, 6.0, -45.0,90.0, CoordType_FL);
//        gelem.save();
        
//        MSG251_GraphElem gelem2(47,4);
//        gelem2.setColor(1,200,0,100);
//        //gelem2.setColorContour(0,20,20,100);
//        gelem2.setLineWidth(2);
//        gelem2.setKeyOtog(0);
//        //gelem2.setParasector(std::pair<double,double>(54.724423, 19.808993), 0.0, 2.0, 3.0, 90.0, CoordType_FL);
//        gelem2.setParasector(std::pair<double,double>(0.0,0.0), 90.0, 2.0, 3.0, 90.0, CoordType_XY);
//        gelem2.save();
        
//        MSG251_GraphElem gelem3(47,5);
//        gelem3.setColor(1,200,0,100);
//        //gelem2.setColorContour(0,20,20,100);
//        gelem3.setLineWidth(2);
//        //gelem3.setKeyOtog(0);
//        //gelem3.setParasector(std::pair<double,double>(54.754423, 19.808993), -40.0, 1.0, 8.0, 90.0, CoordType_FL);
//        gelem3.setParasector(std::pair<double,double>(0.0,0.0), -40.0, 1.0, 8.0, 90.0, CoordType_XY);
//        gelem3.save();

        MSG251_GraphElem gelem4(47,6);
        gelem4.setColor(0,120,120,220);
        gelem4.setLineWidth(2.0);
        gelem4.setKeyOtog(0);

        std::vector< std::pair<double,double> > points;
        points.push_back(std::pair<double,double>(10.0,10.0));
        points.push_back(std::pair<double,double>(15.0,15.0));
        points.push_back(std::pair<double,double>(20.0,10.0));
        points.push_back(std::pair<double,double>(10.0,10.0));

        gelem4.setLines(points, CoordType_XYpx);
        gelem4.save();

    } 
    else  
    if(argc > 1 && argv[1][0] == 'T')
    {   
        MSG451_Trajectory traj(sys.getTaskNum(),2);
        traj.setKeyOtog(0);
        double X = 0.0;
        double Y = 0.0;
        double F=0.0,L=0.0;
        CXYFL(sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),X,Y,&F,&L);
        //printf("CXYFL: %d\n",CXYFL(sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),X,Y,&F,&L));
        //printf("FL: %.2f : %.2f\n", F, L);
        traj.addPoint(F,L, 150, 0, 0.0, 25.0, 25.0, 0.0, MSG450Rotate_ROT_NONE, 0);
        
        Y += 3.75;
        //X -= 4.0;
        CXYFL(sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),X,Y,&F,&L);
        traj.addPoint(F,L, 150, 150, 0.0, 35.0, 35.0, 0.0, MSG450Rotate_ROT_LEFT, 2.5);
        traj.save();
        
        
        MSG451_Trajectory traj1(sys.getTaskNum(),3);
        traj1.setKeyOtog(196611);
        X = 5.0;
        Y = 10.0;
        F=0.0;
        L=0.0;
        printf("CXYFL: %d\n",CXYFL(sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),X,Y,&F,&L));
        printf("FL: %.2f : %.2f\n", F, L);
        traj1.addPoint(F,L, 300, 0, 270.0, 25.0, 25.0, 0.0, MSG450Rotate_ROT_NONE, 0);
        //X += cos(M_PI/3)*5;
        /*Y += 3.75;
        CXYFL(sys.ourShip.getFgrad(),sys.ourShip.getLgrad(),X,Y,&F,&L);
        traj.addPoint(F,L, 400, 40, 0.0, 25.0, 25.0, MSG450Rotate_ROT_LEFT, 5.0);
        */
        traj1.save();
        
        //sleep(1);
        
        MSG453_TrajectoryShow trajShow;
        trajShow.setTrajNumTaskNum(0,sys.getTaskNum());
        trajShow.save();
    }
// 	msg1.setSourNum(OtogSour_PODV,3);
//     int i=1000;
//     double D = 7.3;
//     while(i--)
//     {
//         sleep(1);
//         D += 0.1;
//         msg1.setDml(D);
//         msg1.save();
//     }

    ourShip.setFgrad(54.734423);
    ourShip.setLgrad(19.838993);
    ourShip.save();
//    msg1.setSourNum(OtogSour_PODV,3);
//     int i=1000;
//     double D = 7.3;
//     while(i--)
//     {
//         sleep(1);
//         D += 0.1;
//         msg1.setDml(D);
//         msg1.save();
//     }
    
	return 0;
}
