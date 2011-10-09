#ifndef __PATCH_H__
#define __PATCH_H__

extern /*readonly*/ int numNbrs;

struct force {
  BigReal x;
  BigReal y;
  BigReal z;
};

class ParticleForceMsg : public CMessage_ParticleForceMsg {
  public:
    int lengthX;
    int lengthY;
    int lengthZ;

    force* forces;
    int lengthUpdates;
};

class loc{
  public:
    BigReal x;
    BigReal y;
    BigReal z;

    void pup(PUP::er &p){
      p|x; p|y; p|z;
    }
};

class partData{
  public:
    loc coord;
    BigReal charge;
    
    void pup(PUP::er &p){
      p|coord; p|charge; 
    }
};

class ParticleDataMsg : public CkMcastBaseMsg, public CMessage_ParticleDataMsg {
  public:
    partData* part;
    int lengthAll;
    int x;
    int y;
    int z;
    bool updateList;
    bool deleteList;
    bool doAtSync;
    bool lbOn;

    void pup(PUP::er &p){
      CMessage_ParticleDataMsg::pup(p);
      p | lengthAll;
      p | x; p | y; p | z;
      p | updateList;
      p | deleteList;
      p | doAtSync;
      p | lbOn;
      if (p.isUnpacking()){
	part = new partData[lengthAll];
      }
      PUParray(p, part, lengthAll);
    } 
};

/** \class Patch
 *  Class representing a cell in the grid. 
 *  We consider each cell as a square of LxL units
 */
class Patch : public CBase_Patch {
  private:
    CkVec<Particle> particles;
    CkVec<Particle> incomingParticles;
    int forceCount;		// to count the returns from interactions
    int stepCount;		// to count the number of steps, and decide when to stop
    int updateCount;
    int myNumParts;
    bool updateFlag;
    bool incomingFlag;
    bool pause;
    int **computesList;
    int resumeCount;
    double loadTime;
    int inbrs;
    
 
    void migrateToPatch(Particle p, int &px, int &py, int &pz);
    void updateProperties();	// updates properties after receiving forces from computes
    void applyForces();
    void limitVelocity(Particle &p);
    Particle& wrapAround(Particle &p);
    void print();		// prints all its particles
    CProxySection_Compute mCastSecProxy;

  public:
    Patch();
    Patch(CkMigrateMessage *msg);
    ~Patch();

    void start();
    void createComputes();
    void createSection();
    void localCreateSection();
    void receiveParticles(CkVec<Particle> &);
    void reduceForces(CkReductionMsg *msg);
    void ResumeFromSync();           
    void resume();
    void ftresume();
    void receiveForces(ParticleForceMsg *updates);
    void checkNextStep();	// checks whether to continue with next step
    
    void pup(PUP::er &p){
      CBase_Patch::pup(p); 
      p | particles;
      p | incomingParticles;

      p | forceCount;		
      p | stepCount;		
      p | updateCount;
      p | myNumParts;
      p | updateFlag;
      p | incomingFlag;
      p | pause;
      p | resumeCount;
      p | loadTime;
      p | inbrs;

      if (p.isUnpacking()){
	computesList = new int*[inbrs];
	for (int i = 0; i < inbrs; i++){
	  computesList[i] = new int[6];
	}
      }

      for (int i = 0; i < inbrs; i++){
        PUParray(p, computesList[i], 6);
      }
     
#ifdef USE_SECTION_MULTICAST 
      if (p.isUnpacking()){
        //need to recreate ckmulticast section proxy
	localCreateSection();
      }
#endif
 
    } 

};

#endif
