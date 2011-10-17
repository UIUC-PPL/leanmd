#ifndef __DEFS__
#define __DEFS__

#include "pup.h"

typedef double BigReal;

#define HYDROGEN_MASS          (1.67 * pow( 10.0,-24))
#define VDW_A			      (1.60694452 * pow(10.0, -134))
#define VDW_B			      (1.031093844 * pow(10.0, -77))

#define ENERGY_VAR  		(1.0 * pow(10.0,-5))
#define PARTICLES_PER_PATCH	100

#define DEFAULT_DELTA		1	// in femtoseconds

#define DEFAULT_FIRST_LDB	20
#define DEFAULT_LDB_PERIOD	20
#define DEFAULT_FT_PERIOD	100000

#define PATCHARRAY_DIM_X	3
#define PATCHARRAY_DIM_Y	3
#define PATCHARRAY_DIM_Z	3
#define PTP_CUT_OFF		12	//  cut off for atom to atom interactions
#define PATCH_MARGIN		4 	// constant difference between cut off and patch size
#define PATCH_SIZE_X		(PTP_CUT_OFF + PATCH_MARGIN)
#define PATCH_SIZE_Y		(PTP_CUT_OFF + PATCH_MARGIN)
#define PATCH_SIZE_Z		(PTP_CUT_OFF + PATCH_MARGIN)
#define PATCH_ORIGIN_X		0
#define PATCH_ORIGIN_Y		0
#define PATCH_ORIGIN_Z		0

#define MIGRATE_STEPCOUNT	20
#define DEFAULT_FINALSTEPCOUNT	1001
#define MAX_VELOCITY		30.0

#define KAWAY_X			1
#define KAWAY_Y			1
#define KAWAY_Z			1
#define NBRS_X			(2*KAWAY_X+1)
#define NBRS_Y			(2*KAWAY_Y+1)
#define NBRS_Z			(2*KAWAY_Z+1)
#define NUM_NEIGHBORS		(NBRS_X * NBRS_Y * NBRS_Z)

#define WRAP_X(a)		(((a)+patchArrayDimX)%patchArrayDimX)
#define WRAP_Y(a)		(((a)+patchArrayDimY)%patchArrayDimY)
#define WRAP_Z(a)		(((a)+patchArrayDimZ)%patchArrayDimZ)

// Class for keeping track of the properties for a particle
class Particle {
  public:

    int id;
    BigReal mass;	// mass of the particle
    BigReal charge;     // charge of particle
    BigReal x;		// position in x axis
    BigReal y;		// position in y axis
    BigReal z;		// position in z axis

    BigReal fx;		// total forces on x axis
    BigReal fy;		// total forces on y axis
    BigReal fz;		// total forces on z axis

    BigReal ax;		// acceleration on x axis
    BigReal ay;		// acceleration on y axis
    BigReal az;		// acceleration on z axis

    BigReal vx;		// velocity on x axis
    BigReal vy;		// velocity on y axis
    BigReal vz;		// velocity on z axis

    // Default constructor
    Particle() {
      fx = fy = fz = 0.0;
    }

    // Function for pupping properties
    void pup(PUP::er &p) {
      p | id; p | mass; p | charge;
      p | x;  p | y;  p | z;
      p | fx; p | fy; p | fz;
      p | ax; p | ay; p | az;
      p | vx; p | vy; p | vz;
    }
};
#endif
