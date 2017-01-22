//some shapes (regular or half-regular)

// --------------------------------------------


// Phi (actually the conjugate of phi) is (sqrt(5) - 1) / 2
#declare  phi = 0.61803398874989484820458683436563811772;

// sqrt2 is sqrt(2)
#declare sqrt2 = 1.4142135623730950488016887242096980786;

// ------------------------------------
//initalizing regular direction-vector-sets and normalizing them
        //1: TC (tetrahedron corners)
        //2: CF (cube faces)
        //3: CC (cube corners)
        //4: CE (cube edges)
        //5: DF (dodecahedron faces)
        //6: DC (dodecahedron corners)
        //7: DE (dodecahedron edges)
        //8: CW (triakis octahedron)
        //9: DeltIcosi (Deltoidal Icositetrahedron)

#declare dirsTC=array [4]{ <1,1,1>,<1,-1,-1>,<-1,1,-1>,<-1,-1,1>};
#declare dirsCF=array [6]{	<0,0,1>,<0,0,-1>,<0,1,0>,<0,-1,0>,<1,0,0>,<-1,0,0>};
#declare dirsCC=array [8]{
	<1,1,1>,<-1,-1,-1>,<-1,1,1>,<1,-1,-1>,
	<1,-1,1>,<-1,1,-1>,<1,1,-1>,<-1,-1,1>};
#declare dirsCE=array [12]{
	<0,1,1>,<0,-1,-1>,<0,-1,1>,<0,1,-1>,
	<1,1,0>,<-1,-1,0>,<-1,1,0>,<1,-1,0>,
	<1,0,1>,<-1,0,-1>,<1,0,-1>,<-1,0,1>};
#declare dirsDF=array [12]{
	<0,1,phi>,<0,-1,-phi>,<0,-1,phi>,<0,1,-phi>,
	<1,phi,0>,<-1,-phi,0>,<-1,phi,0>,<1,-phi,0>,
	<phi,0,1>,<-phi,0,-1>,<phi,0,-1>,<-phi,0,1>};
#declare dirsDC=array [20]{
	<1,1,1>,<-1,-1,-1>,<-1,1,1>,<1,-1,-1>,
	<1,-1,1>,<-1,1,-1>,<1,1,-1>,<-1,-1,1>,
	<0,1,phi+2>,<0,-1,-phi-2>,<0,-1,phi+2>,<0,1,-phi-2>,
	<1,phi+2,0>,<-1,-phi-2,0>,<-1,phi+2,0>,<1,-phi-2,0>,
	<phi+2,0,1>,<-phi-2,0,-1>,<phi+2,0,-1>,<-phi-2,0,1>};
#declare dirsDE=array [30]{
	<0,0,1>,<0,0,-1>,<0,1,0>,<0,-1,0>,<1,0,0>,<-1,0,0>,
	<1,1+phi,phi>,<phi,1,1+phi>,<1+phi,phi,1>,
	<1,1+phi,-phi>,<phi,1,-1-phi>,<1+phi,phi,-1>,
	<1,-1-phi,phi>,<phi,-1,1+phi>,<1+phi,-phi,1>,
	<1,-1-phi,-phi>,<phi,-1,-1-phi>,<1+phi,-phi,-1>,
	<-1,1+phi,phi>,<-phi,1,1+phi>,<-1-phi,phi,1>,
	<-1,1+phi,-phi>,<-phi,1,-1-phi>,<-1-phi,phi,-1>,
	<-1,-1-phi,phi>,<-phi,-1,1+phi>,<-1-phi,-phi,1>,
	<-1,-1-phi,-phi>,<-phi,-1,-1-phi>,<-1-phi,-phi,-1>};

// triakis octahedron
// dwing is 2 * (sqrt(2) - 1)
#declare dwing = 0.82842712474619009760337744841939615714;
#declare dirsCW=array [24] {
    < dwing,2,-2>,
    <-dwing,2,-2>,
    <-2,2,-dwing>,
    <-2,2, dwing>,
    <-dwing,2, 2>,
    < dwing,2, 2>,
    < 2,2, dwing>,
    < 2,2,-dwing>,

    < 2,dwing,-2>,
    <-2,dwing,-2>,
    <-2,dwing, 2>,
    < 2,dwing, 2>,
    < 2,-dwing,-2>,
    <-2,-dwing,-2>,
    <-2,-dwing, 2>,
    < 2,-dwing, 2>,

    < dwing,-2,-2>,
    <-dwing,-2,-2>,
    <-2,-2,-dwing>,
    <-2,-2, dwing>,
    <-dwing,-2, 2>,
    < dwing,-2, 2>,
    < 2,-2, dwing>,
    < 2,-2,-dwing>,
}


// Deltoidal Icositetrahedron
// Using dual Rhombicuboctahedron for axis system

#declare dirsDeltIcosi=array [24] {
	 <1, 1, 1 + sqrt2>,
	 <1, 1, -1 - sqrt2>,
	 <1, -1, 1 + sqrt2>,
	 <1, -1, -1 - sqrt2>,
	 <-1, 1, 1 + sqrt2>,
	 <-1, 1, -1 - sqrt2>,
	 <-1, -1, 1 + sqrt2>,
	 <-1, -1, -1 - sqrt2>,
	 <1, 1 + sqrt2, 1>,
	 <1, -1 - sqrt2, 1>,
	 <1, 1 + sqrt2, -1>,
	 <1, -1 - sqrt2, -1>,
	 <-1, 1 + sqrt2, 1>,
	 <-1, -1 - sqrt2, 1>,
	 <-1, 1 + sqrt2, -1>,
	 <-1, -1 - sqrt2, -1>,
	 <1 + sqrt2, 1, 1>,
	 <-1 - sqrt2, 1, 1>,
	 <1 + sqrt2, 1, -1>,
	 <-1 - sqrt2, 1, -1>,
	 <1 + sqrt2, -1, 1>,
	 <-1 - sqrt2, -1, 1>,
	 <1 + sqrt2, -1, -1>,
	 <-1 - sqrt2, -1, -1>,
}


// DeltoidalHexecontahedron
// Using dual Rhombicosidodecahedron for axis system

// (1 + sqrt(5)) / 4
#declare delt_hex_c0 = 0.80901699437494742410229341718281905886;

// (3 + sqrt(5)) / 4
#declare delt_hex_c1 = 1.3090169943749474241022934171828190589;

// (1 + sqrt(5)) / 2
#declare delt_hex_c2 = 1.6180339887498948482045868343656381177;

// (5 + sqrt(5)) / 4
#declare delt_hex_c3 = 1.8090169943749474241022934171828190589;

// (2 + sqrt(5)) / 2
#declare delt_hex_c4 = 2.1180339887498948482045868343656381177;

#declare dirsDeltHex=array [60] {
	 < 0.5, 0.5, delt_hex_c4>,
	 < 0.5, 0.5, -delt_hex_c4>,
	 < 0.5, -0.5, delt_hex_c4>,
	 < 0.5, -0.5, -delt_hex_c4>,
	 <-0.5, 0.5, delt_hex_c4>,
	 <-0.5, 0.5, -delt_hex_c4>,
	 <-0.5, -0.5, delt_hex_c4>,
	 <-0.5, -0.5, -delt_hex_c4>,
	 < delt_hex_c4, 0.5, 0.5>,
	 < delt_hex_c4, 0.5, -0.5>,
	 < delt_hex_c4, -0.5, 0.5>,
	 < delt_hex_c4, -0.5, -0.5>,
	 < -delt_hex_c4, 0.5, 0.5>,
	 < -delt_hex_c4, 0.5, -0.5>,
	 < -delt_hex_c4, -0.5, 0.5>,
	 < -delt_hex_c4, -0.5, -0.5>,
	 < 0.5, delt_hex_c4, 0.5>,
	 < 0.5, delt_hex_c4, -0.5>,
	 < 0.5, -delt_hex_c4, 0.5>,
	 < 0.5, -delt_hex_c4, -0.5>,
	 <-0.5, delt_hex_c4, 0.5>,
	 <-0.5, delt_hex_c4, -0.5>,
	 <-0.5, -delt_hex_c4, 0.5>,
	 <-0.5, -delt_hex_c4, -0.5>,
	 < 0.0, delt_hex_c1, delt_hex_c3>,
	 < 0.0, delt_hex_c1, -delt_hex_c3>,
	 < 0.0, -delt_hex_c1, delt_hex_c3>,
	 < 0.0, -delt_hex_c1, -delt_hex_c3>,
	 < delt_hex_c3, 0.0, delt_hex_c1>,
	 < delt_hex_c3, 0.0, -delt_hex_c1>,
	 < -delt_hex_c3, 0.0, delt_hex_c1>,
	 < -delt_hex_c3, 0.0, -delt_hex_c1>,
	 < delt_hex_c1, delt_hex_c3, 0.0>,
	 < delt_hex_c1, -delt_hex_c3, 0.0>,
	 < -delt_hex_c1, delt_hex_c3, 0.0>,
	 < -delt_hex_c1, -delt_hex_c3, 0.0>,
	 < delt_hex_c1, delt_hex_c0, delt_hex_c2>,
	 < delt_hex_c1, delt_hex_c0, -delt_hex_c2>,
	 < delt_hex_c1, -delt_hex_c0, delt_hex_c2>,
	 < delt_hex_c1, -delt_hex_c0, -delt_hex_c2>,
	 < -delt_hex_c1, delt_hex_c0, delt_hex_c2>,
	 < -delt_hex_c1, delt_hex_c0, -delt_hex_c2>,
	 < -delt_hex_c1, -delt_hex_c0, delt_hex_c2>,
	 < -delt_hex_c1, -delt_hex_c0, -delt_hex_c2>,
	 < delt_hex_c2, delt_hex_c1, delt_hex_c0>,
	 < delt_hex_c2, delt_hex_c1, -delt_hex_c0>,
	 < delt_hex_c2, -delt_hex_c1, delt_hex_c0>,
	 < delt_hex_c2, -delt_hex_c1, -delt_hex_c0>,
	 < -delt_hex_c2, delt_hex_c1, delt_hex_c0>,
	 < -delt_hex_c2, delt_hex_c1, -delt_hex_c0>,
	 < -delt_hex_c2, -delt_hex_c1, delt_hex_c0>,
	 < -delt_hex_c2, -delt_hex_c1, -delt_hex_c0>,
	 < delt_hex_c0, delt_hex_c2, delt_hex_c1>,
	 < delt_hex_c0, delt_hex_c2, -delt_hex_c1>,
	 < delt_hex_c0, -delt_hex_c2, delt_hex_c1>,
	 < delt_hex_c0, -delt_hex_c2, -delt_hex_c1>,
	 < -delt_hex_c0, delt_hex_c2, delt_hex_c1>,
	 < -delt_hex_c0, delt_hex_c2, -delt_hex_c1>,
	 < -delt_hex_c0, -delt_hex_c2, delt_hex_c1>,
	 < -delt_hex_c0, -delt_hex_c2, -delt_hex_c1>,
}


// Triakis Tetrahedron
// Using dual Truncated Tetrahedron for axis system

// sqrt(2) / 4
#declare tria_tet_c0 = 0.35355339059327376220042218105242451964;

// (3 * sqrt(2)) / 4
#declare tria_tet_c1 = 1.0606601717798212866012665431572735589;

#declare dirsTriaTet=array [12] {
	 < tria_tet_c0, -tria_tet_c0,  tria_tet_c1>,
	 < tria_tet_c0,  tria_tet_c0, -tria_tet_c1>,
	 <-tria_tet_c0,  tria_tet_c0,  tria_tet_c1>,
	 <-tria_tet_c0, -tria_tet_c0, -tria_tet_c1>,
	 < tria_tet_c1, -tria_tet_c0,  tria_tet_c0>,
	 < tria_tet_c1,  tria_tet_c0, -tria_tet_c0>,
	 <-tria_tet_c1,  tria_tet_c0,  tria_tet_c0>,
	 <-tria_tet_c1, -tria_tet_c0, -tria_tet_c0>,
	 < tria_tet_c0, -tria_tet_c1,  tria_tet_c0>,
	 < tria_tet_c0,  tria_tet_c1, -tria_tet_c0>,
	 <-tria_tet_c0,  tria_tet_c1,  tria_tet_c0>,
	 <-tria_tet_c0, -tria_tet_c1, -tria_tet_c0>,
}


// Tetrakis Hexahedron
// Using dual Truncated Octahedron for axis system

#declare dirsTetraHex=array [24] {
	 < (sqrt2 / 2.0), 0.0,  sqrt2>,
	 < (sqrt2 / 2.0), 0.0, -sqrt2>,
	 <-(sqrt2 / 2.0), 0.0,  sqrt2>,
	 <-(sqrt2 / 2.0), 0.0, -sqrt2>,
	 < sqrt2,  (sqrt2 / 2.0), 0.0>,
	 < sqrt2, -(sqrt2 / 2.0), 0.0>,
	 <-sqrt2,  (sqrt2 / 2.0), 0.0>,
	 <-sqrt2, -(sqrt2 / 2.0), 0.0>,
	 <0.0,  sqrt2,  (sqrt2 / 2.0)>,
	 <0.0,  sqrt2, -(sqrt2 / 2.0)>,
	 <0.0, -sqrt2,  (sqrt2 / 2.0)>,
	 <0.0, -sqrt2, -(sqrt2 / 2.0)>,
	 <0.0,  (sqrt2 / 2.0),  sqrt2>,
	 <0.0,  (sqrt2 / 2.0), -sqrt2>,
	 <0.0, -(sqrt2 / 2.0),  sqrt2>,
	 <0.0, -(sqrt2 / 2.0), -sqrt2>,
	 < sqrt2, 0.0,  (sqrt2 / 2.0)>,
	 < sqrt2, 0.0, -(sqrt2 / 2.0)>,
	 <-sqrt2, 0.0,  (sqrt2 / 2.0)>,
	 <-sqrt2, 0.0, -(sqrt2 / 2.0)>,
	 < (sqrt2 / 2.0),  sqrt2, 0.0>,
	 < (sqrt2 / 2.0), -sqrt2, 0.0>,
	 <-(sqrt2 / 2.0),  sqrt2, 0.0>,
	 <-(sqrt2 / 2.0), -sqrt2, 0.0>,
}


// Pentagonal Icositetrahedron (dextro)
// Using dual Snub Cube (laevo) for axis system

// (1 + cbrt(19 - 3*sqrt(33)) + cbrt(19 + 3*sqrt(33))) / 3
#declare pent_icosi_c1 = 1.8392867552141611325518525646532866004;

// laevo coords
#declare dirsPentIcosiD=array [24] {
	 < pent_icosi_c1,  1,  (1.0 / pent_icosi_c1)>,
	 < pent_icosi_c1, -1, -(1.0 / pent_icosi_c1)>,
	 <-pent_icosi_c1, -1,  (1.0 / pent_icosi_c1)>,
	 <-pent_icosi_c1,  1, -(1.0 / pent_icosi_c1)>,
	 < (1.0 / pent_icosi_c1),  pent_icosi_c1,  1>,
	 < (1.0 / pent_icosi_c1), -pent_icosi_c1, -1>,
	 <-(1.0 / pent_icosi_c1), -pent_icosi_c1,  1>,
	 <-(1.0 / pent_icosi_c1),  pent_icosi_c1, -1>,
	 < 1,  (1.0 / pent_icosi_c1),  pent_icosi_c1>,
	 < 1, -(1.0 / pent_icosi_c1), -pent_icosi_c1>,
	 <-1, -(1.0 / pent_icosi_c1),  pent_icosi_c1>,
	 <-1,  (1.0 / pent_icosi_c1), -pent_icosi_c1>,
	 < 1, -pent_icosi_c1,  (1.0 / pent_icosi_c1)>,
	 < 1,  pent_icosi_c1, -(1.0 / pent_icosi_c1)>,
	 <-1,  pent_icosi_c1,  (1.0 / pent_icosi_c1)>,
	 <-1, -pent_icosi_c1, -(1.0 / pent_icosi_c1)>,
	 < (1.0 / pent_icosi_c1), -1,  pent_icosi_c1>,
	 < (1.0 / pent_icosi_c1),  1, -pent_icosi_c1>,
	 <-(1.0 / pent_icosi_c1),  1,  pent_icosi_c1>,
	 <-(1.0 / pent_icosi_c1), -1, -pent_icosi_c1>,
	 < pent_icosi_c1, -(1.0 / pent_icosi_c1),  1>,
	 < pent_icosi_c1,  (1.0 / pent_icosi_c1), -1>,
	 <-pent_icosi_c1,  (1.0 / pent_icosi_c1),  1>,
	 <-pent_icosi_c1, -(1.0 / pent_icosi_c1), -1>,
}


// dextro coords
#declare dirsPentIcosiL=array [24] {
	 < pent_icosi_c1, -1,  (1.0 / pent_icosi_c1)>,
	 < pent_icosi_c1,  1, -(1.0 / pent_icosi_c1)>,
	 <-pent_icosi_c1,  1,  (1.0 / pent_icosi_c1)>,
	 <-pent_icosi_c1, -1, -(1.0 / pent_icosi_c1)>,
	 < (1.0 / pent_icosi_c1), -pent_icosi_c1,  1>,
	 < (1.0 / pent_icosi_c1),  pent_icosi_c1, -1>,
	 <-(1.0 / pent_icosi_c1),  pent_icosi_c1,  1>,
	 <-(1.0 / pent_icosi_c1), -pent_icosi_c1, -1>,
	 < 1, -(1.0 / pent_icosi_c1),  pent_icosi_c1>,
	 < 1,  (1.0 / pent_icosi_c1), -pent_icosi_c1>,
	 <-1,  (1.0 / pent_icosi_c1),  pent_icosi_c1>,
	 <-1, -(1.0 / pent_icosi_c1), -pent_icosi_c1>,
	 < 1,  pent_icosi_c1,  (1.0 / pent_icosi_c1)>,
	 < 1, -pent_icosi_c1, -(1.0 / pent_icosi_c1)>,
	 <-1, -pent_icosi_c1,  (1.0 / pent_icosi_c1)>,
	 <-1,  pent_icosi_c1, -(1.0 / pent_icosi_c1)>,
	 < (1.0 / pent_icosi_c1),  1,  pent_icosi_c1>,
	 < (1.0 / pent_icosi_c1), -1, -pent_icosi_c1>,
	 <-(1.0 / pent_icosi_c1), -1,  pent_icosi_c1>,
	 <-(1.0 / pent_icosi_c1),  1, -pent_icosi_c1>,
	 < pent_icosi_c1,  (1.0 / pent_icosi_c1),  1>,
	 < pent_icosi_c1, -(1.0 / pent_icosi_c1), -1>,
	 <-pent_icosi_c1, -(1.0 / pent_icosi_c1),  1>,
	 <-pent_icosi_c1,  (1.0 / pent_icosi_c1), -1>,
}


// Disdyakis Dodecahedron
// Using dual truncated octahedron for axis system

// 1 + sqrt(2)
#declare disdy_dodeca_c0 = 2.4142135623730950488016887242096980786;

// 1 + 2 * sqrt(2)
#declare disdy_dodeca_c1 = 3.8284271247461900976033774484193961571;

#declare dirsDisdyDodeca=array [48] {
	 <  disdy_dodeca_c0,  1,   disdy_dodeca_c1>,
	 <  disdy_dodeca_c0,  1,  -disdy_dodeca_c1>,
	 <  disdy_dodeca_c0, -1,   disdy_dodeca_c1>,
	 <  disdy_dodeca_c0, -1,  -disdy_dodeca_c1>,
	 < -disdy_dodeca_c0,  1,   disdy_dodeca_c1>,
	 < -disdy_dodeca_c0,  1,  -disdy_dodeca_c1>,
	 < -disdy_dodeca_c0, -1,   disdy_dodeca_c1>,
	 < -disdy_dodeca_c0, -1,  -disdy_dodeca_c1>,
	 <  disdy_dodeca_c1,   disdy_dodeca_c0,  1>,
	 <  disdy_dodeca_c1,   disdy_dodeca_c0, -1>,
	 <  disdy_dodeca_c1,  -disdy_dodeca_c0,  1>,
	 <  disdy_dodeca_c1,  -disdy_dodeca_c0, -1>,
	 < -disdy_dodeca_c1,   disdy_dodeca_c0,  1>,
	 < -disdy_dodeca_c1,   disdy_dodeca_c0, -1>,
	 < -disdy_dodeca_c1,  -disdy_dodeca_c0,  1>,
	 < -disdy_dodeca_c1,  -disdy_dodeca_c0, -1>,
	 < 1,   disdy_dodeca_c1,   disdy_dodeca_c0>,
	 < 1,   disdy_dodeca_c1,  -disdy_dodeca_c0>,
	 < 1,  -disdy_dodeca_c1,   disdy_dodeca_c0>,
	 < 1,  -disdy_dodeca_c1,  -disdy_dodeca_c0>,
	 <-1,   disdy_dodeca_c1,   disdy_dodeca_c0>,
	 <-1,   disdy_dodeca_c1,  -disdy_dodeca_c0>,
	 <-1,  -disdy_dodeca_c1,   disdy_dodeca_c0>,
	 <-1,  -disdy_dodeca_c1,  -disdy_dodeca_c0>,
	 < 1,   disdy_dodeca_c0,   disdy_dodeca_c1>,
	 < 1,   disdy_dodeca_c0,  -disdy_dodeca_c1>,
	 < 1,  -disdy_dodeca_c0,   disdy_dodeca_c1>,
	 < 1,  -disdy_dodeca_c0,  -disdy_dodeca_c1>,
	 <-1,   disdy_dodeca_c0,   disdy_dodeca_c1>,
	 <-1,   disdy_dodeca_c0,  -disdy_dodeca_c1>,
	 <-1,  -disdy_dodeca_c0,   disdy_dodeca_c1>,
	 <-1,  -disdy_dodeca_c0,  -disdy_dodeca_c1>,
	 <  disdy_dodeca_c1,  1,   disdy_dodeca_c0>,
	 <  disdy_dodeca_c1,  1,  -disdy_dodeca_c0>,
	 <  disdy_dodeca_c1, -1,   disdy_dodeca_c0>,
	 <  disdy_dodeca_c1, -1,  -disdy_dodeca_c0>,
	 < -disdy_dodeca_c1,  1,   disdy_dodeca_c0>,
	 < -disdy_dodeca_c1,  1,  -disdy_dodeca_c0>,
	 < -disdy_dodeca_c1, -1,   disdy_dodeca_c0>,
	 < -disdy_dodeca_c1, -1,  -disdy_dodeca_c0>,
	 <  disdy_dodeca_c0,   disdy_dodeca_c1,  1>,
	 <  disdy_dodeca_c0,   disdy_dodeca_c1, -1>,
	 <  disdy_dodeca_c0,  -disdy_dodeca_c1,  1>,
	 <  disdy_dodeca_c0,  -disdy_dodeca_c1, -1>,
	 < -disdy_dodeca_c0,   disdy_dodeca_c1,  1>,
	 < -disdy_dodeca_c0,   disdy_dodeca_c1, -1>,
	 < -disdy_dodeca_c0,  -disdy_dodeca_c1,  1>,
	 < -disdy_dodeca_c0,  -disdy_dodeca_c1, -1>,
}


// Pentakis Dodecahedron
// Using dual truncated icosahedron for axis system

// (1 + sqrt(5)) / 2
#declare penta_dodeca_c0 = 1.6180339887498948482045868343656381177;

// 1 + sqrt(5)
#declare penta_dodeca_c1 = 3.2360679774997896964091736687312762354;

// (5 + sqrt(5)) / 2
#declare penta_dodeca_c2 = 3.6180339887498948482045868343656381177;

// 2 + sqrt(5)
#declare penta_dodeca_c3 = 4.2360679774997896964091736687312762354;

// (3 * (1 + sqrt(5))) / 2
#declare penta_dodeca_c4 = 4.8541019662496845446137605030969143532;

#declare dirsPentaDodeca=array [60] {
	 < 1.0,  0.0,   penta_dodeca_c4>,
	 < 1.0,  0.0,  -penta_dodeca_c4>,
	 <-1.0,  0.0,   penta_dodeca_c4>,
	 <-1.0,  0.0,  -penta_dodeca_c4>,
	 <  penta_dodeca_c4,  1.0,  0.0>,
	 <  penta_dodeca_c4, -1.0,  0.0>,
	 < -penta_dodeca_c4,  1.0,  0.0>,
	 < -penta_dodeca_c4, -1.0,  0.0>,
	 < 0.0,   penta_dodeca_c4,  1.0>,
	 < 0.0,   penta_dodeca_c4, -1.0>,
	 < 0.0,  -penta_dodeca_c4,  1.0>,
	 < 0.0,  -penta_dodeca_c4, -1.0>,
	 < 2.0,   penta_dodeca_c0,   penta_dodeca_c3>,
	 < 2.0,   penta_dodeca_c0,  -penta_dodeca_c3>,
	 < 2.0,  -penta_dodeca_c0,   penta_dodeca_c3>,
	 < 2.0,  -penta_dodeca_c0,  -penta_dodeca_c3>,
	 <-2.0,   penta_dodeca_c0,   penta_dodeca_c3>,
	 <-2.0,   penta_dodeca_c0,  -penta_dodeca_c3>,
	 <-2.0,  -penta_dodeca_c0,   penta_dodeca_c3>,
	 <-2.0,  -penta_dodeca_c0,  -penta_dodeca_c3>,
	 <  penta_dodeca_c3,  2.0,   penta_dodeca_c0>,
	 <  penta_dodeca_c3,  2.0,  -penta_dodeca_c0>,
	 <  penta_dodeca_c3, -2.0,   penta_dodeca_c0>,
	 <  penta_dodeca_c3, -2.0,  -penta_dodeca_c0>,
	 < -penta_dodeca_c3,  2.0,   penta_dodeca_c0>,
	 < -penta_dodeca_c3,  2.0,  -penta_dodeca_c0>,
	 < -penta_dodeca_c3, -2.0,   penta_dodeca_c0>,
	 < -penta_dodeca_c3, -2.0,  -penta_dodeca_c0>,
	 <  penta_dodeca_c0,   penta_dodeca_c3,  2.0>,
	 <  penta_dodeca_c0,   penta_dodeca_c3, -2.0>,
	 <  penta_dodeca_c0,  -penta_dodeca_c3,  2.0>,
	 <  penta_dodeca_c0,  -penta_dodeca_c3, -2.0>,
	 < -penta_dodeca_c0,   penta_dodeca_c3,  2.0>,
	 < -penta_dodeca_c0,   penta_dodeca_c3, -2.0>,
	 < -penta_dodeca_c0,  -penta_dodeca_c3,  2.0>,
	 < -penta_dodeca_c0,  -penta_dodeca_c3, -2.0>,
	 < 1.0,   penta_dodeca_c1,   penta_dodeca_c2>,
	 < 1.0,   penta_dodeca_c1,  -penta_dodeca_c2>,
	 < 1.0,  -penta_dodeca_c1,   penta_dodeca_c2>,
	 < 1.0,  -penta_dodeca_c1,  -penta_dodeca_c2>,
	 <-1.0,   penta_dodeca_c1,   penta_dodeca_c2>,
	 <-1.0,   penta_dodeca_c1,  -penta_dodeca_c2>,
	 <-1.0,  -penta_dodeca_c1,   penta_dodeca_c2>,
	 <-1.0,  -penta_dodeca_c1,  -penta_dodeca_c2>,
	 <  penta_dodeca_c2,  1.0,   penta_dodeca_c1>,
	 <  penta_dodeca_c2,  1.0,  -penta_dodeca_c1>,
	 <  penta_dodeca_c2, -1.0,   penta_dodeca_c1>,
	 <  penta_dodeca_c2, -1.0,  -penta_dodeca_c1>,
	 < -penta_dodeca_c2,  1.0,   penta_dodeca_c1>,
	 < -penta_dodeca_c2,  1.0,  -penta_dodeca_c1>,
	 < -penta_dodeca_c2, -1.0,   penta_dodeca_c1>,
	 < -penta_dodeca_c2, -1.0,  -penta_dodeca_c1>,
	 <  penta_dodeca_c1,   penta_dodeca_c2,  1.0>,
	 <  penta_dodeca_c1,   penta_dodeca_c2, -1.0>,
	 <  penta_dodeca_c1,  -penta_dodeca_c2,  1.0>,
	 <  penta_dodeca_c1,  -penta_dodeca_c2, -1.0>,
	 < -penta_dodeca_c1,   penta_dodeca_c2,  1.0>,
	 < -penta_dodeca_c1,   penta_dodeca_c2, -1.0>,
	 < -penta_dodeca_c1,  -penta_dodeca_c2,  1.0>,
	 < -penta_dodeca_c1,  -penta_dodeca_c2, -1.0>,
}


// Triakis Icosahedron
// Using dual truncated dodecahedron for axis system

// (3 + sqrt(5)) / 2
#declare tria_icosa_c0 = 2.6180339887498948482045868343656381177;

// 1 + sqrt(5)
#declare tria_icosa_c1 = 3.2360679774997896964091736687312762354;

// 2 + sqrt(5)
#declare tria_icosa_c2 = 4.2360679774997896964091736687312762354;

// 3 + sqrt(5)
#declare tria_icosa_c3 = 5.2360679774997896964091736687312762354;

// (5 + (3 * sqrt(5))) / 2
#declare tria_icosa_c4 = 5.8541019662496845446137605030969143531;

#declare dirsTriaIcosa=array [60] {
	 < 0.0,  1,   tria_icosa_c4>,
	 < 0.0,  1,  -tria_icosa_c4>,
	 < 0.0, -1,   tria_icosa_c4>,
	 < 0.0, -1,  -tria_icosa_c4>,
	 <  tria_icosa_c4,  0.0,  1>,
	 <  tria_icosa_c4,  0.0, -1>,
	 < -tria_icosa_c4,  0.0,  1>,
	 < -tria_icosa_c4,  0.0, -1>,
	 < 1,   tria_icosa_c4,  0.0>,
	 < 1,  -tria_icosa_c4,  0.0>,
	 <-1,   tria_icosa_c4,  0.0>,
	 <-1,  -tria_icosa_c4,  0.0>,
	 < 1,   tria_icosa_c0,   tria_icosa_c3>,
	 < 1,   tria_icosa_c0,  -tria_icosa_c3>,
	 < 1,  -tria_icosa_c0,   tria_icosa_c3>,
	 < 1,  -tria_icosa_c0,  -tria_icosa_c3>,
	 <-1,   tria_icosa_c0,   tria_icosa_c3>,
	 <-1,   tria_icosa_c0,  -tria_icosa_c3>,
	 <-1,  -tria_icosa_c0,   tria_icosa_c3>,
	 <-1,  -tria_icosa_c0,  -tria_icosa_c3>,
	 <  tria_icosa_c3,  1,   tria_icosa_c0>,
	 <  tria_icosa_c3,  1,  -tria_icosa_c0>,
	 <  tria_icosa_c3, -1,   tria_icosa_c0>,
	 <  tria_icosa_c3, -1,  -tria_icosa_c0>,
	 < -tria_icosa_c3,  1,   tria_icosa_c0>,
	 < -tria_icosa_c3,  1,  -tria_icosa_c0>,
	 < -tria_icosa_c3, -1,   tria_icosa_c0>,
	 < -tria_icosa_c3, -1,  -tria_icosa_c0>,
	 <  tria_icosa_c0,   tria_icosa_c3,  1>,
	 <  tria_icosa_c0,   tria_icosa_c3, -1>,
	 <  tria_icosa_c0,  -tria_icosa_c3,  1>,
	 <  tria_icosa_c0,  -tria_icosa_c3, -1>,
	 < -tria_icosa_c0,   tria_icosa_c3,  1>,
	 < -tria_icosa_c0,   tria_icosa_c3, -1>,
	 < -tria_icosa_c0,  -tria_icosa_c3,  1>,
	 < -tria_icosa_c0,  -tria_icosa_c3, -1>,
	 <  tria_icosa_c0,   tria_icosa_c1,   tria_icosa_c2>,
	 <  tria_icosa_c0,   tria_icosa_c1,  -tria_icosa_c2>,
	 <  tria_icosa_c0,  -tria_icosa_c1,   tria_icosa_c2>,
	 <  tria_icosa_c0,  -tria_icosa_c1,  -tria_icosa_c2>,
	 < -tria_icosa_c0,   tria_icosa_c1,   tria_icosa_c2>,
	 < -tria_icosa_c0,   tria_icosa_c1,  -tria_icosa_c2>,
	 < -tria_icosa_c0,  -tria_icosa_c1,   tria_icosa_c2>,
	 < -tria_icosa_c0,  -tria_icosa_c1,  -tria_icosa_c2>,
	 <  tria_icosa_c2,   tria_icosa_c0,   tria_icosa_c1>,
	 <  tria_icosa_c2,   tria_icosa_c0,  -tria_icosa_c1>,
	 <  tria_icosa_c2,  -tria_icosa_c0,   tria_icosa_c1>,
	 <  tria_icosa_c2,  -tria_icosa_c0,  -tria_icosa_c1>,
	 < -tria_icosa_c2,   tria_icosa_c0,   tria_icosa_c1>,
	 < -tria_icosa_c2,   tria_icosa_c0,  -tria_icosa_c1>,
	 < -tria_icosa_c2,  -tria_icosa_c0,   tria_icosa_c1>,
	 < -tria_icosa_c2,  -tria_icosa_c0,  -tria_icosa_c1>,
	 <  tria_icosa_c1,   tria_icosa_c2,   tria_icosa_c0>,
	 <  tria_icosa_c1,   tria_icosa_c2,  -tria_icosa_c0>,
	 <  tria_icosa_c1,  -tria_icosa_c2,   tria_icosa_c0>,
	 <  tria_icosa_c1,  -tria_icosa_c2,  -tria_icosa_c0>,
	 < -tria_icosa_c1,   tria_icosa_c2,   tria_icosa_c0>,
	 < -tria_icosa_c1,   tria_icosa_c2,  -tria_icosa_c0>,
	 < -tria_icosa_c1,  -tria_icosa_c2,   tria_icosa_c0>,
	 < -tria_icosa_c1,  -tria_icosa_c2,  -tria_icosa_c0>,
}


// Pentagonal Hexecontahedron
// Using dual snub dodecahedron for axis system

// root of 4096*x^12 - 15360*x^10 + 18944*x^8 - 7168*x^6 + 1024*x^4 - 56*x^2 + 1 near 0.19289371135
#declare pent_hexe_c0 = 0.19289371135235902210826254606058370628;

// root of 4096*x^12 - 12288*x^10 + 15872*x^8 - 6016*x^6 + 912*x^4 - 56*x^2 + 1 near 0.330921024729
#declare pent_hexe_c1 = 0.33092102472984423096365526918724901949;

// root of 4096*x^12 + 6144*x^10 + 4352*x^8 - 3456*x^6 + 672*x^4 - 48*x^2 + 1 near 0.3748216581
#declare pent_hexe_c2 = 0.37482165811456229526660951660834472834;

// root of 4096*x^12 - 3072*x^10 + 9728*x^8 - 8960*x^6 + 2944*x^4 - 328*x^2 + 1 near 0.56771536946
#declare pent_hexe_c3 = 0.56771536946692131737487206266892843462;

// root of 4096*x^12 - 5120*x^10 + 9472*x^8 - 5888*x^6 + 1216*x^4 - 68*x^2 + 1 near 0.643029605914072
#declare pent_hexe_c4 = 0.64302960591407257310746414144061142920;

// root of 4096*x^12 - 1024*x^10 + 4096*x^8 - 4672*x^6 + 1392*x^4 - 128*x^2 + 1 near 0.72833517695
#declare pent_hexe_c5 = 0.72833517695719147736067162983752079476;

// root of 4096*x^12 + 3072*x^10 - 3584*x^8 - 2048*x^6 + 1312*x^4 - 160*x^2 + 1 near 0.8475500467
#declare pent_hexe_c6 = 0.84755004678906079739621795603029949819;

// root of 4096*x^12 - 17408*x^10 + 28672*x^8 - 21696*x^6 + 6672*x^4 - 416*x^2 + 1 near 1.103156835
#declare pent_hexe_c7 = 1.1031568350717537726272811464458655231;

// root of 4096*x^12 - 9728*x^8 - 3072*x^6 + 4256*x^4 - 132*x^2 + 1 near 1.2495037884
#declare pent_hexe_c8 = 1.2495037884630271950077410963179867418;

// root of 4096*x^12 - 18432*x^10 + 29184*x^8 - 20160*x^6 + 5728*x^4 - 488*x^2 + 1 near 1.41526541625
#declare pent_hexe_c9 = 1.4152654162559821147710900186992279328;

// root of 4096*x^12 - 8192*x^10 + 1792*x^8 - 7488*x^6 + 3456*x^4 - 116*x^2 + 1 near 1.4540242293
#declare pent_hexe_c10 = 1.4540242293380154192964949109076748108;

// root of 4096*x^12 - 13312*x^10 + 9216*x^8 - 9472*x^6 + 1872*x^4 - 100*x^2 + 1 near 1.64691794
#declare pent_hexe_c11 = 1.6469179406903744414047574569682585171;

// root of 4096*x^12 - 12288*x^10 - 768*x^8 + 384*x^6 + 272*x^4 - 36*x^2 + 1 near 1.746186440
#declare pent_hexe_c12 = 1.7461864409858263457347452878864769523;

// root of 4096*x^12 - 19456*x^10 + 14592*x^8 - 4736*x^6 + 752*x^4 - 48*x^2 + 1 near 1.9778389654
#declare pent_hexe_c13 = 1.9778389654202186723684127261555075366;

// root of 4096*x^12 - 21504*x^10 + 16384*x^8 - 4672*x^6 + 624*x^4 - 40*x^2 + 1
#declare pent_hexe_c14 = 2.0970538352520879924039590523482862400;

#declare dirsPentHexeD=array [60] {
	 <  pent_hexe_c2,  -pent_hexe_c1,  pent_hexe_c14>,
	 <  pent_hexe_c2,   pent_hexe_c1, -pent_hexe_c14>,
	 < -pent_hexe_c2,   pent_hexe_c1,  pent_hexe_c14>,
	 < -pent_hexe_c2,  -pent_hexe_c1, -pent_hexe_c14>,
	 < pent_hexe_c14,  -pent_hexe_c2,   pent_hexe_c1>,
	 < pent_hexe_c14,   pent_hexe_c2,  -pent_hexe_c1>,
	 <-pent_hexe_c14,   pent_hexe_c2,   pent_hexe_c1>,
	 <-pent_hexe_c14,  -pent_hexe_c2,  -pent_hexe_c1>,
	 <  pent_hexe_c1, -pent_hexe_c14,   pent_hexe_c2>,
	 <  pent_hexe_c1,  pent_hexe_c14,  -pent_hexe_c2>,
	 < -pent_hexe_c1,  pent_hexe_c14,   pent_hexe_c2>,
	 < -pent_hexe_c1, -pent_hexe_c14,  -pent_hexe_c2>,
	 <  pent_hexe_c3,   pent_hexe_c4,  pent_hexe_c13>,
	 <  pent_hexe_c3,  -pent_hexe_c4, -pent_hexe_c13>,
	 < -pent_hexe_c3,  -pent_hexe_c4,  pent_hexe_c13>,
	 < -pent_hexe_c3,   pent_hexe_c4, -pent_hexe_c13>,
	 < pent_hexe_c13,   pent_hexe_c3,   pent_hexe_c4>,
	 < pent_hexe_c13,  -pent_hexe_c3,  -pent_hexe_c4>,
	 <-pent_hexe_c13,  -pent_hexe_c3,   pent_hexe_c4>,
	 <-pent_hexe_c13,   pent_hexe_c3,  -pent_hexe_c4>,
	 <  pent_hexe_c4,  pent_hexe_c13,   pent_hexe_c3>,
	 <  pent_hexe_c4, -pent_hexe_c13,  -pent_hexe_c3>,
	 < -pent_hexe_c4, -pent_hexe_c13,   pent_hexe_c3>,
	 < -pent_hexe_c4,  pent_hexe_c13,  -pent_hexe_c3>,
	 <  pent_hexe_c0,  -pent_hexe_c8,  pent_hexe_c12>,
	 <  pent_hexe_c0,   pent_hexe_c8, -pent_hexe_c12>,
	 < -pent_hexe_c0,   pent_hexe_c8,  pent_hexe_c12>,
	 < -pent_hexe_c0,  -pent_hexe_c8, -pent_hexe_c12>,
	 < pent_hexe_c12,  -pent_hexe_c0,   pent_hexe_c8>,
	 < pent_hexe_c12,   pent_hexe_c0,  -pent_hexe_c8>,
	 <-pent_hexe_c12,   pent_hexe_c0,   pent_hexe_c8>,
	 <-pent_hexe_c12,  -pent_hexe_c0,  -pent_hexe_c8>,
	 <  pent_hexe_c8, -pent_hexe_c12,   pent_hexe_c0>,
	 <  pent_hexe_c8,  pent_hexe_c12,  -pent_hexe_c0>,
	 < -pent_hexe_c8,  pent_hexe_c12,   pent_hexe_c0>,
	 < -pent_hexe_c8, -pent_hexe_c12,  -pent_hexe_c0>,
	 <  pent_hexe_c7,  -pent_hexe_c6,  pent_hexe_c11>,
	 <  pent_hexe_c7,   pent_hexe_c6, -pent_hexe_c11>,
	 < -pent_hexe_c7,   pent_hexe_c6,  pent_hexe_c11>,
	 < -pent_hexe_c7,  -pent_hexe_c6, -pent_hexe_c11>,
	 < pent_hexe_c11,  -pent_hexe_c7,   pent_hexe_c6>,
	 < pent_hexe_c11,   pent_hexe_c7,  -pent_hexe_c6>,
	 <-pent_hexe_c11,   pent_hexe_c7,   pent_hexe_c6>,
	 <-pent_hexe_c11,  -pent_hexe_c7,  -pent_hexe_c6>,
	 <  pent_hexe_c6, -pent_hexe_c11,   pent_hexe_c7>,
	 <  pent_hexe_c6,  pent_hexe_c11,  -pent_hexe_c7>,
	 < -pent_hexe_c6,  pent_hexe_c11,   pent_hexe_c7>,
	 < -pent_hexe_c6, -pent_hexe_c11,  -pent_hexe_c7>,
	 <  pent_hexe_c9,   pent_hexe_c5,  pent_hexe_c10>,
	 <  pent_hexe_c9,  -pent_hexe_c5, -pent_hexe_c10>,
	 < -pent_hexe_c9,  -pent_hexe_c5,  pent_hexe_c10>,
	 < -pent_hexe_c9,   pent_hexe_c5, -pent_hexe_c10>,
	 < pent_hexe_c10,   pent_hexe_c9,   pent_hexe_c5>,
	 < pent_hexe_c10,  -pent_hexe_c9,  -pent_hexe_c5>,
	 <-pent_hexe_c10,  -pent_hexe_c9,   pent_hexe_c5>,
	 <-pent_hexe_c10,   pent_hexe_c9,  -pent_hexe_c5>,
	 <  pent_hexe_c5,  pent_hexe_c10,   pent_hexe_c9>,
	 <  pent_hexe_c5, -pent_hexe_c10,  -pent_hexe_c9>,
	 < -pent_hexe_c5, -pent_hexe_c10,   pent_hexe_c9>,
	 < -pent_hexe_c5,  pent_hexe_c10,  -pent_hexe_c9>,
}


#declare dirsPentHexeL=array [60] {
	 <  pent_hexe_c2,   pent_hexe_c1,  pent_hexe_c14>,
	 <  pent_hexe_c2,  -pent_hexe_c1, -pent_hexe_c14>,
	 < -pent_hexe_c2,  -pent_hexe_c1,  pent_hexe_c14>,
	 < -pent_hexe_c2,   pent_hexe_c1, -pent_hexe_c14>,
	 < pent_hexe_c14,   pent_hexe_c2,   pent_hexe_c1>,
	 < pent_hexe_c14,  -pent_hexe_c2,  -pent_hexe_c1>,
	 <-pent_hexe_c14,  -pent_hexe_c2,   pent_hexe_c1>,
	 <-pent_hexe_c14,   pent_hexe_c2,  -pent_hexe_c1>,
	 <  pent_hexe_c1,  pent_hexe_c14,   pent_hexe_c2>,
	 <  pent_hexe_c1, -pent_hexe_c14,  -pent_hexe_c2>,
	 < -pent_hexe_c1, -pent_hexe_c14,   pent_hexe_c2>,
	 < -pent_hexe_c1,  pent_hexe_c14,  -pent_hexe_c2>,
	 <  pent_hexe_c3,  -pent_hexe_c4,  pent_hexe_c13>,
	 <  pent_hexe_c3,   pent_hexe_c4, -pent_hexe_c13>,
	 < -pent_hexe_c3,   pent_hexe_c4,  pent_hexe_c13>,
	 < -pent_hexe_c3,  -pent_hexe_c4, -pent_hexe_c13>,
	 < pent_hexe_c13,  -pent_hexe_c3,   pent_hexe_c4>,
	 < pent_hexe_c13,   pent_hexe_c3,  -pent_hexe_c4>,
	 <-pent_hexe_c13,   pent_hexe_c3,   pent_hexe_c4>,
	 <-pent_hexe_c13,  -pent_hexe_c3,  -pent_hexe_c4>,
	 <  pent_hexe_c4, -pent_hexe_c13,   pent_hexe_c3>,
	 <  pent_hexe_c4,  pent_hexe_c13,  -pent_hexe_c3>,
	 < -pent_hexe_c4,  pent_hexe_c13,   pent_hexe_c3>,
	 < -pent_hexe_c4, -pent_hexe_c13,  -pent_hexe_c3>,
	 <  pent_hexe_c0,   pent_hexe_c8,  pent_hexe_c12>,
	 <  pent_hexe_c0,  -pent_hexe_c8, -pent_hexe_c12>,
	 < -pent_hexe_c0,  -pent_hexe_c8,  pent_hexe_c12>,
	 < -pent_hexe_c0,   pent_hexe_c8, -pent_hexe_c12>,
	 < pent_hexe_c12,   pent_hexe_c0,   pent_hexe_c8>,
	 < pent_hexe_c12,  -pent_hexe_c0,  -pent_hexe_c8>,
	 <-pent_hexe_c12,  -pent_hexe_c0,   pent_hexe_c8>,
	 <-pent_hexe_c12,   pent_hexe_c0,  -pent_hexe_c8>,
	 <  pent_hexe_c8,  pent_hexe_c12,   pent_hexe_c0>,
	 <  pent_hexe_c8, -pent_hexe_c12,  -pent_hexe_c0>,
	 < -pent_hexe_c8, -pent_hexe_c12,   pent_hexe_c0>,
	 < -pent_hexe_c8,  pent_hexe_c12,  -pent_hexe_c0>,
	 <  pent_hexe_c7,   pent_hexe_c6,  pent_hexe_c11>,
	 <  pent_hexe_c7,  -pent_hexe_c6, -pent_hexe_c11>,
	 < -pent_hexe_c7,  -pent_hexe_c6,  pent_hexe_c11>,
	 < -pent_hexe_c7,   pent_hexe_c6, -pent_hexe_c11>,
	 < pent_hexe_c11,   pent_hexe_c7,   pent_hexe_c6>,
	 < pent_hexe_c11,  -pent_hexe_c7,  -pent_hexe_c6>,
	 <-pent_hexe_c11,  -pent_hexe_c7,   pent_hexe_c6>,
	 <-pent_hexe_c11,   pent_hexe_c7,  -pent_hexe_c6>,
	 <  pent_hexe_c6,  pent_hexe_c11,   pent_hexe_c7>,
	 <  pent_hexe_c6, -pent_hexe_c11,  -pent_hexe_c7>,
	 < -pent_hexe_c6, -pent_hexe_c11,   pent_hexe_c7>,
	 < -pent_hexe_c6,  pent_hexe_c11,  -pent_hexe_c7>,
	 <  pent_hexe_c9,  -pent_hexe_c5,  pent_hexe_c10>,
	 <  pent_hexe_c9,   pent_hexe_c5, -pent_hexe_c10>,
	 < -pent_hexe_c9,   pent_hexe_c5,  pent_hexe_c10>,
	 < -pent_hexe_c9,  -pent_hexe_c5, -pent_hexe_c10>,
	 < pent_hexe_c10,  -pent_hexe_c9,   pent_hexe_c5>,
	 < pent_hexe_c10,   pent_hexe_c9,  -pent_hexe_c5>,
	 <-pent_hexe_c10,   pent_hexe_c9,   pent_hexe_c5>,
	 <-pent_hexe_c10,  -pent_hexe_c9,  -pent_hexe_c5>,
	 <  pent_hexe_c5, -pent_hexe_c10,   pent_hexe_c9>,
	 <  pent_hexe_c5,  pent_hexe_c10,  -pent_hexe_c9>,
	 < -pent_hexe_c5,  pent_hexe_c10,   pent_hexe_c9>,
	 < -pent_hexe_c5, -pent_hexe_c10,  -pent_hexe_c9>,
}


// Triangular Dipyramid
// Using dual Triangular Prism for axis system

// sqrt(3) / 6
#declare tri_dipyra_c0 = 0.28867513459481288225457439025097872782;

// sqrt(3) / 3
#declare tri_dipyra_c1 = 0.57735026918962576450914878050195745565;

#declare dirsTriDipyra=array [6] {
	 < 0.0,  0.5,  tri_dipyra_c1>,
	 < 0.0, -0.5,  tri_dipyra_c1>,
 	 <-0.5,  0.5,  -tri_dipyra_c0>,
  	 <-0.5, -0.5,  -tri_dipyra_c0>,
  	 < 0.5,  0.5,  -tri_dipyra_c0>,
  	 < 0.5, -0.5,  -tri_dipyra_c0>,
}


// Pentagonal Dipyramid
// Using dual Pentagonal Prism for axis system

// sqrt((1/10) * (5 + sqrt(5)))
#declare pent_dipyra_c0 = 0.85065080835203993218154049706301107224;

// (1/2) * sqrt((1/5) * (5 + 2 * sqrt(5)))
#declare pent_dipyra_c1 = 0.68819096023558676910360479095544383976;

// (1/4) * (1 + sqrt(5))
#declare pent_dipyra_c2 = 0.80901699437494742410229341718281905886;

// 1 / sqrt(2 * (5 + sqrt(5)))
#declare pent_dipyra_c3 = 0.26286555605956680301283454242393830364;

#declare dirsPentDipyra=array [10] {
	 < 0.0,  0.5, pent_dipyra_c0>,
	 < pent_dipyra_c2,  0.5, pent_dipyra_c3>,
 	 <-pent_dipyra_c2,  0.5, pent_dipyra_c3>,
	 < 0.5,  0.5, -pent_dipyra_c1>,
 	 <-0.5,  0.5, -pent_dipyra_c1>,
 	 < 0.0, -0.5, pent_dipyra_c0>,
	 < pent_dipyra_c2, -0.5, pent_dipyra_c3>,
 	 <-pent_dipyra_c2, -0.5, pent_dipyra_c3>,
	 < 0.5, -0.5, -pent_dipyra_c1>,
 	 <-0.5, -0.5, -pent_dipyra_c1>,
}


// Hexagonal Dipyramid
// Using dual Hexagonal Prism for axis system

// sqrt(3) / 2
#declare hex_dipyra_c0 = 0.86602540378443864676372317075293618347;

#declare dirsHexDipyra=array [12] {
	 < 0.0,  0.5,  1>,
	 < hex_dipyra_c0,  0.5,  0.5>,
 	 < hex_dipyra_c0,  0.5, -0.5>,
 	 < 0.0,  0.5,  -1>,
  	 <-hex_dipyra_c0,  0.5, -0.5>,
   	 <-hex_dipyra_c0,  0.5,  0.5>,
 	 < 0.0, -0.5,  1>,
	 < hex_dipyra_c0, -0.5,  0.5>,
 	 < hex_dipyra_c0, -0.5, -0.5>,
 	 < 0.0, -0.5,  -1>,
  	 <-hex_dipyra_c0, -0.5, -0.5>,
   	 <-hex_dipyra_c0, -0.5,  0.5>,
}


#macro normalize (dirset)
    #local length=dimension_size(dirset,1);
    #local i=0;

    #while(i<length)
        #declare dirset[i]=dirset[i]/vlength(dirset[i]);
    #local i=i+1;
    #end
#end

//normalize all dirs
normalize(dirsTC)
normalize(dirsCF)
normalize(dirsCC)
normalize(dirsCE)
normalize(dirsDF)
normalize(dirsDC)
normalize(dirsDE)
normalize(dirsCW)
normalize(dirsDeltIcosi)
normalize(dirsDeltHex)
normalize(dirsTriaTet)
normalize(dirsTetraHex)
normalize(dirsPentIcosiD)
normalize(dirsPentIcosiL)
normalize(dirsDisdyDodeca)
normalize(dirsPentaDodeca)
normalize(dirsTriaIcosa)
normalize(dirsPentHexeD)
normalize(dirsPentHexeL)
normalize(dirsTriDipyra)
normalize(dirsPentDipyra)
normalize(dirsHexDipyra)


#macro intersect_shape(shape, dirset)
       #local length = dimension_size(dirset, 1);

       #declare shape = plane {dirset[0], 1};
       #local i = 1;
       #while(i < length)
           #declare shape = intersection{
	   	    object{shape}
		    plane {dirset[i], 1}
		    };
           #local i = i + 1;
       #end
#end

// ------------------------------------

// Sphere
#declare shSphere = sphere{0, 1.0};

#declare shTet = 0;
intersect_shape(shTet, dirsTC)

//cube
#declare shCube = 0;
intersect_shape(shCube, dirsCF)

//regular octahedron
#declare shOct = 0;
intersect_shape(shOct, dirsCC)

//rhombic dodecahedron
#declare shRhDod = 0;
intersect_shape(shRhDod, dirsCE)

//regular dodecahedron
#declare shDod = 0;
intersect_shape(shDod, dirsDF)

//regular icosahedron
#declare shIco = 0;
intersect_shape(shIco, dirsDC)

//rhombic triacontahedron
#declare shRhTriacon = 0;
intersect_shape(shRhTriacon, dirsDE)

//triakis octahedron
#declare shCW = 0;
intersect_shape(shCW, dirsCW)

// Deltoidal Icositetrahedron
#declare shDeltIcosi = 0;
intersect_shape(shDeltIcosi, dirsDeltIcosi)

// Deltoidal Hexecontahedron
#declare shDeltHex = 0;
intersect_shape(shDeltHex, dirsDeltHex)

// Triakis Tetrahedron
#declare shTriaTet = 0;
intersect_shape(shTriaTet, dirsTriaTet)

// Tetrakis Hexahedron
#declare shTetraHex = 0;
intersect_shape(shTetraHex, dirsTetraHex)

// Pentagonal Icositetrahedron (dextro)
#declare shPentIcosiD = 0;
intersect_shape(shPentIcosiD, dirsPentIcosiD)

// Pentagonal Icositetrahedron (laveo)
#declare shPentIcosiL = 0;
intersect_shape(shPentIcosiL, dirsPentIcosiL)

// Disdyakis Dodecahedron
#declare shDisdyDodeca = 0;
intersect_shape(shDisdyDodeca, dirsDisdyDodeca)

// Pentakis Dodecahedron
#declare shPentaDodeca = 0;
intersect_shape(shPentaDodeca, dirsPentaDodeca)

// Triakis Icosahedron
#declare shTriaIcosa = 0;
intersect_shape(shTriaIcosa, dirsTriaIcosa)

// Pentagonal Hexecontahedron (dextro)
#declare shPentHexeD = 0;
intersect_shape(shPentHexeD, dirsPentHexeD)

// Pentagonal Hexecontahedron (laevo)
#declare shPentHexeL = 0;
intersect_shape(shPentHexeL, dirsPentHexeL)

// Triangular Dipyramid
#declare shTriDipyra = 0;
intersect_shape(shTriDipyra, dirsTriDipyra)

// Pentagonal Dipyramid
#declare shPentDipyra = 0;
intersect_shape(shPentDipyra, dirsPentDipyra)

// Hexagonal Dipyramid
#declare shHexDipyra = 0;
intersect_shape(shHexDipyra, dirsHexDipyra)
