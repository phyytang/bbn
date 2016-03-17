#include "src/bbnio.h"

/*--------------------------------------------------------*/
/* Calculation of the observables in the Standard Model   */
/* Included is the Fierz interference term, which extends */
/* the electroweak sector to include scalar and tensor    */
/* currents that may result from SUSY, leptoquarks, etc   */
/*--------------------------------------------------------*/
int main(int argc,char** argv)
{ 
	double eta, nbnu, tau, fierz;

	if(argc<5) 
  	{ 
        printf(" This program needs 4 parameters:\n"
            "   eta     value of the baryon-to-photon ratio\n"
            "   nbnu    number of neutrinos\n"
            "   tau     neutron lifetime\n"
            "   fierz   beta-decay Fierz interference term\n");
        exit(1); 
  	} 
	else 
  	{
  		sscanf(argv[1],"%lf",&eta);
  		sscanf(argv[2],"%lf",&nbnu);
  		sscanf(argv[3],"%lf",&tau);
  		sscanf(argv[4],"%lf",&fierz);
  	}
	
	CosmologyModel relic;      /// The parameters from the big bang relic before bbn.
	relic.Init_cosmomodel();	
	relic.Init_fierz(eta,nbnu,tau,fierz);
	
	NuclideMap ratioH, sigma_ratioH;
	NuclideIndex ni[6] = {He4,H2,He3,Li7,Li6,Be7};	/// only display this subset

	printf("Primary central values:\n");	
    compute_ratios(relic, ni, ratioH, sigma_ratioH);
    //compute_constraints(relic, ni, ratioH);
    bbn_excluded(0, relic, ni, ratioH);
	
	printf("\nGnuplot formated bounded range.\n");
	print_lables_bounds("eta", ni);
	//print_lables_bounds("Fierz b", ni);
    //for (double b = fierz - 0.2; b <= fierz + 0.2; b += 0.01) {
	//relic.fierz = b;
    for (eta = 1e-10; eta < 10e-10; eta*=pow(10,0.1))
	{
		relic.Init_fierz(eta,nbnu,tau,fierz);
        if(nucl_witherrors(3, relic, ratioH, sigma_ratioH))
        {
            //print_ratios("value:", ni, ratioH);
            //print_ratios("  +/-:", ni, sigma_ratioH);
            //print_ratios_errors(b, ni, ratioH, sigma_ratioH);
            print_ratios_error_bounds(eta, ni, ratioH, sigma_ratioH);
        }
    }
}
