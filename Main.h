#ifndef __MAIN_H__
#define __MAIN_H__

class Main : public CBase_Main {
  private:
    int phase;
    double energy, prevEnergy;
    int testFailed;

  public:
    Main(CkArgMsg* msg);
    Main(CkMigrateMessage* msg);
    void pup(PUP::er &p) {
      Chare::pup(p);
      p|phase;
      p|energy;
      p|prevEnergy;
      p|testFailed;
    }

    void allDone();
    void ftBarrier();
    void startUpDone();
    void energySumP(double energyP);
    void energySumK(double energyK);
};
#endif
