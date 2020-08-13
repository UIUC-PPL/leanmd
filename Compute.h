#ifndef __COMPUTE_H__
#define __COMPUTE_H__

#include "defs.h"

// Class representing the interaction agents between a couple of cells
class Compute : public CBase_Compute {
  private:
    Compute_SDAG_CODE
    int stepCount; // Current step number
    double energy[2]; // Store potential energy
    // Handles to differentiate the two multicast sections I am part of
    CkSectionInfo mcast1;
    CkSectionInfo mcast2;

  public:
    Compute();
    Compute(CkMigrateMessage *msg);
    void pup(PUP::er &p);

    void selfInteract(ParticleDataMsg *msg);
    void interact(ParticleDataMsg *msg1, ParticleDataMsg *msg2);
};

#endif
