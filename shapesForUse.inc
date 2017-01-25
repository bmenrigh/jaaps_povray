//some shapes (regular or half-regular)

// --------------------------------------------

#macro normalize (dirset)
    #local length=dimension_size(dirset,1);
    #local i=0;

    #while(i<length)
        #declare dirset[i]=dirset[i]/vlength(dirset[i]);
    #local i=i+1;
    #end
#end

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


// This function requires a shape to already be created
// but it allows you to control the distance of the faces
#macro intersect_shape_r(shape, dirset, r)
       #local length = dimension_size(dirset, 1);

       #local i = 0;
       #while(i < length)
           #declare shape = intersection{
	   	    object{shape}
		    plane {dirset[i], r}
		    };
           #local i = i + 1;
       #end
#end


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

#declare dirsTC=array [4] {
	 <1,1,1>,<1,-1,-1>,<-1,1,-1>,<-1,-1,1>
};
normalize(dirsTC)

#declare dirsCF=array [6] {
	 <0,0,1>,<0,0,-1>,<0,1,0>,<0,-1,0>,<1,0,0>,<-1,0,0>
};
normalize(dirsCF)


#declare dirsCC=array [8]{
	<1,1,1>,<-1,-1,-1>,<-1,1,1>,<1,-1,-1>,
	<1,-1,1>,<-1,1,-1>,<1,1,-1>,<-1,-1,1>
};
normalize(dirsCC)

#declare dirsCE=array [12]{
	<0,1,1>,<0,-1,-1>,<0,-1,1>,<0,1,-1>,
	<1,1,0>,<-1,-1,0>,<-1,1,0>,<1,-1,0>,
	<1,0,1>,<-1,0,-1>,<1,0,-1>,<-1,0,1>
};
normalize(dirsCE)

#declare dirsDF=array [12]{
	<0,1,phi>,<0,-1,-phi>,<0,-1,phi>,<0,1,-phi>,
	<1,phi,0>,<-1,-phi,0>,<-1,phi,0>,<1,-phi,0>,
	<phi,0,1>,<-phi,0,-1>,<phi,0,-1>,<-phi,0,1>
};
normalize(dirsDF)

#declare dirsDC=array [20]{
	<1,1,1>,<-1,-1,-1>,<-1,1,1>,<1,-1,-1>,
	<1,-1,1>,<-1,1,-1>,<1,1,-1>,<-1,-1,1>,
	<0,1,phi+2>,<0,-1,-phi-2>,<0,-1,phi+2>,<0,1,-phi-2>,
	<1,phi+2,0>,<-1,-phi-2,0>,<-1,phi+2,0>,<1,-phi-2,0>,
	<phi+2,0,1>,<-phi-2,0,-1>,<phi+2,0,-1>,<-phi-2,0,1>
};
normalize(dirsDC)

#declare dirsDE=array [30]{
	<0,0,1>,<0,0,-1>,<0,1,0>,<0,-1,0>,<1,0,0>,<-1,0,0>,
	<1,1+phi,phi>,<phi,1,1+phi>,<1+phi,phi,1>,
	<1,1+phi,-phi>,<phi,1,-1-phi>,<1+phi,phi,-1>,
	<1,-1-phi,phi>,<phi,-1,1+phi>,<1+phi,-phi,1>,
	<1,-1-phi,-phi>,<phi,-1,-1-phi>,<1+phi,-phi,-1>,
	<-1,1+phi,phi>,<-phi,1,1+phi>,<-1-phi,phi,1>,
	<-1,1+phi,-phi>,<-phi,1,-1-phi>,<-1-phi,phi,-1>,
	<-1,-1-phi,phi>,<-phi,-1,1+phi>,<-1-phi,-phi,1>,
	<-1,-1-phi,-phi>,<-phi,-1,-1-phi>,<-1-phi,-phi,-1>
};
normalize(dirsDE)

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
normalize(dirsCW)


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
normalize(dirsDeltIcosi)


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
normalize(dirsDeltHex)


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
normalize(dirsTriaTet)


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
normalize(dirsTetraHex)


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
normalize(dirsPentIcosiD)


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
normalize(dirsPentIcosiL)


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
normalize(dirsDisdyDodeca)


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
normalize(dirsPentaDodeca)


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
normalize(dirsTriaIcosa)


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
normalize(dirsPentHexeD)


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
normalize(dirsPentHexeL)


// Disdyakis Triacontahedron
// Using dual Truncated Icosidodecahedron for axis system

// (3 + sqrt(5)) / 2
#declare disdy_tria_c0 = 2.6180339887498948482045868343656381177;

// 1 + sqrt(5)
#declare disdy_tria_c1 = 3.2360679774997896964091736687312762354;

// (5 + sqrt(5)) / 2
#declare disdy_tria_c2 = 3.6180339887498948482045868343656381177;

// 2 + sqrt(5)
#declare disdy_tria_c3 = 4.2360679774997896964091736687312762354;

// (3 * (1 + sqrt(5))) / 2
#declare disdy_tria_c4 = 4.8541019662496845446137605030969143532;

// 3 + sqrt(5)
#declare disdy_tria_c5 = 5.2360679774997896964091736687312762354;

// ((5 + 3 * sqrt(5))) / 2
#declare disdy_tria_c6 = 5.8541019662496845446137605030969143531;

// 4 + sqrt(5)
#declare disdy_tria_c7 = 6.2360679774997896964091736687312762354;

// (7 + 3 * sqrt(5)) / 2
#declare disdy_tria_c8 = 6.8541019662496845446137605030969143531;

// (3 + 2 * sqrt(5))
#declare disdy_tria_c9 = 7.4721359549995793928183473374625524709;

#declare dirsDisdyTria=array [120] {
	 < 1.0,  1.0,   disdy_tria_c9>,
	 < 1.0,  1.0,  -disdy_tria_c9>,
	 < 1.0, -1.0,   disdy_tria_c9>,
	 < 1.0, -1.0,  -disdy_tria_c9>,
	 <-1.0,  1.0,   disdy_tria_c9>,
	 <-1.0,  1.0,  -disdy_tria_c9>,
	 <-1.0, -1.0,   disdy_tria_c9>,
	 <-1.0, -1.0,  -disdy_tria_c9>,
	 <  disdy_tria_c9,  1.0,  1.0>,
	 <  disdy_tria_c9,  1.0, -1.0>,
	 <  disdy_tria_c9, -1.0,  1.0>,
	 <  disdy_tria_c9, -1.0, -1.0>,
	 < -disdy_tria_c9,  1.0,  1.0>,
	 < -disdy_tria_c9,  1.0, -1.0>,
	 < -disdy_tria_c9, -1.0,  1.0>,
	 < -disdy_tria_c9, -1.0, -1.0>,
	 < 1.0,   disdy_tria_c9,  1.0>,
	 < 1.0,   disdy_tria_c9, -1.0>,
	 < 1.0,  -disdy_tria_c9,  1.0>,
	 < 1.0,  -disdy_tria_c9, -1.0>,
	 <-1.0,   disdy_tria_c9,  1.0>,
	 <-1.0,   disdy_tria_c9, -1.0>,
	 <-1.0,  -disdy_tria_c9,  1.0>,
	 <-1.0,  -disdy_tria_c9, -1.0>,
	 < 2.0,   disdy_tria_c0,   disdy_tria_c8>,
	 < 2.0,   disdy_tria_c0,  -disdy_tria_c8>,
	 < 2.0,  -disdy_tria_c0,   disdy_tria_c8>,
	 < 2.0,  -disdy_tria_c0,  -disdy_tria_c8>,
	 <-2.0,   disdy_tria_c0,   disdy_tria_c8>,
	 <-2.0,   disdy_tria_c0,  -disdy_tria_c8>,
	 <-2.0,  -disdy_tria_c0,   disdy_tria_c8>,
	 <-2.0,  -disdy_tria_c0,  -disdy_tria_c8>,
	 <  disdy_tria_c8,  2.0,   disdy_tria_c0>,
	 <  disdy_tria_c8,  2.0,  -disdy_tria_c0>,
	 <  disdy_tria_c8, -2.0,   disdy_tria_c0>,
	 <  disdy_tria_c8, -2.0,  -disdy_tria_c0>,
	 < -disdy_tria_c8,  2.0,   disdy_tria_c0>,
	 < -disdy_tria_c8,  2.0,  -disdy_tria_c0>,
	 < -disdy_tria_c8, -2.0,   disdy_tria_c0>,
	 < -disdy_tria_c8, -2.0,  -disdy_tria_c0>,
	 <  disdy_tria_c0,   disdy_tria_c8,  2.0>,
	 <  disdy_tria_c0,   disdy_tria_c8, -2.0>,
	 <  disdy_tria_c0,  -disdy_tria_c8,  2.0>,
	 <  disdy_tria_c0,  -disdy_tria_c8, -2.0>,
	 < -disdy_tria_c0,   disdy_tria_c8,  2.0>,
	 < -disdy_tria_c0,   disdy_tria_c8, -2.0>,
	 < -disdy_tria_c0,  -disdy_tria_c8,  2.0>,
	 < -disdy_tria_c0,  -disdy_tria_c8, -2.0>,
	 < 1.0,   disdy_tria_c3,   disdy_tria_c7>,
	 < 1.0,   disdy_tria_c3,  -disdy_tria_c7>,
	 < 1.0,  -disdy_tria_c3,   disdy_tria_c7>,
	 < 1.0,  -disdy_tria_c3,  -disdy_tria_c7>,
	 <-1.0,   disdy_tria_c3,   disdy_tria_c7>,
	 <-1.0,   disdy_tria_c3,  -disdy_tria_c7>,
	 <-1.0,  -disdy_tria_c3,   disdy_tria_c7>,
	 <-1.0,  -disdy_tria_c3,  -disdy_tria_c7>,
	 <  disdy_tria_c7,  1.0,   disdy_tria_c3>,
	 <  disdy_tria_c7,  1.0,  -disdy_tria_c3>,
	 <  disdy_tria_c7, -1.0,   disdy_tria_c3>,
	 <  disdy_tria_c7, -1.0,  -disdy_tria_c3>,
	 < -disdy_tria_c7,  1.0,   disdy_tria_c3>,
	 < -disdy_tria_c7,  1.0,  -disdy_tria_c3>,
	 < -disdy_tria_c7, -1.0,   disdy_tria_c3>,
	 < -disdy_tria_c7, -1.0,  -disdy_tria_c3>,
	 <  disdy_tria_c3,   disdy_tria_c7,  1.0>,
	 <  disdy_tria_c3,   disdy_tria_c7, -1.0>,
	 <  disdy_tria_c3,  -disdy_tria_c7,  1.0>,
	 <  disdy_tria_c3,  -disdy_tria_c7, -1.0>,
	 < -disdy_tria_c3,   disdy_tria_c7,  1.0>,
	 < -disdy_tria_c3,   disdy_tria_c7, -1.0>,
	 < -disdy_tria_c3,  -disdy_tria_c7,  1.0>,
	 < -disdy_tria_c3,  -disdy_tria_c7, -1.0>,
	 <  disdy_tria_c2,   disdy_tria_c1,   disdy_tria_c6>,
	 <  disdy_tria_c2,   disdy_tria_c1,  -disdy_tria_c6>,
	 <  disdy_tria_c2,  -disdy_tria_c1,   disdy_tria_c6>,
	 <  disdy_tria_c2,  -disdy_tria_c1,  -disdy_tria_c6>,
	 < -disdy_tria_c2,   disdy_tria_c1,   disdy_tria_c6>,
	 < -disdy_tria_c2,   disdy_tria_c1,  -disdy_tria_c6>,
	 < -disdy_tria_c2,  -disdy_tria_c1,   disdy_tria_c6>,
	 < -disdy_tria_c2,  -disdy_tria_c1,  -disdy_tria_c6>,
	 <  disdy_tria_c6,   disdy_tria_c2,   disdy_tria_c1>,
	 <  disdy_tria_c6,   disdy_tria_c2,  -disdy_tria_c1>,
	 <  disdy_tria_c6,  -disdy_tria_c2,   disdy_tria_c1>,
	 <  disdy_tria_c6,  -disdy_tria_c2,  -disdy_tria_c1>,
	 < -disdy_tria_c6,   disdy_tria_c2,   disdy_tria_c1>,
	 < -disdy_tria_c6,   disdy_tria_c2,  -disdy_tria_c1>,
	 < -disdy_tria_c6,  -disdy_tria_c2,   disdy_tria_c1>,
	 < -disdy_tria_c6,  -disdy_tria_c2,  -disdy_tria_c1>,
	 <  disdy_tria_c1,   disdy_tria_c6,   disdy_tria_c2>,
	 <  disdy_tria_c1,   disdy_tria_c6,  -disdy_tria_c2>,
	 <  disdy_tria_c1,  -disdy_tria_c6,   disdy_tria_c2>,
	 <  disdy_tria_c1,  -disdy_tria_c6,  -disdy_tria_c2>,
	 < -disdy_tria_c1,   disdy_tria_c6,   disdy_tria_c2>,
	 < -disdy_tria_c1,   disdy_tria_c6,  -disdy_tria_c2>,
	 < -disdy_tria_c1,  -disdy_tria_c6,   disdy_tria_c2>,
	 < -disdy_tria_c1,  -disdy_tria_c6,  -disdy_tria_c2>,
	 <  disdy_tria_c0,   disdy_tria_c4,   disdy_tria_c5>,
	 <  disdy_tria_c0,   disdy_tria_c4,  -disdy_tria_c5>,
	 <  disdy_tria_c0,  -disdy_tria_c4,   disdy_tria_c5>,
	 <  disdy_tria_c0,  -disdy_tria_c4,  -disdy_tria_c5>,
	 < -disdy_tria_c0,   disdy_tria_c4,   disdy_tria_c5>,
	 < -disdy_tria_c0,   disdy_tria_c4,  -disdy_tria_c5>,
	 < -disdy_tria_c0,  -disdy_tria_c4,   disdy_tria_c5>,
	 < -disdy_tria_c0,  -disdy_tria_c4,  -disdy_tria_c5>,
	 <  disdy_tria_c5,   disdy_tria_c0,   disdy_tria_c4>,
	 <  disdy_tria_c5,   disdy_tria_c0,  -disdy_tria_c4>,
	 <  disdy_tria_c5,  -disdy_tria_c0,   disdy_tria_c4>,
	 <  disdy_tria_c5,  -disdy_tria_c0,  -disdy_tria_c4>,
	 < -disdy_tria_c5,   disdy_tria_c0,   disdy_tria_c4>,
	 < -disdy_tria_c5,   disdy_tria_c0,  -disdy_tria_c4>,
	 < -disdy_tria_c5,  -disdy_tria_c0,   disdy_tria_c4>,
	 < -disdy_tria_c5,  -disdy_tria_c0,  -disdy_tria_c4>,
	 <  disdy_tria_c4,   disdy_tria_c5,   disdy_tria_c0>,
	 <  disdy_tria_c4,   disdy_tria_c5,  -disdy_tria_c0>,
	 <  disdy_tria_c4,  -disdy_tria_c5,   disdy_tria_c0>,
	 <  disdy_tria_c4,  -disdy_tria_c5,  -disdy_tria_c0>,
	 < -disdy_tria_c4,   disdy_tria_c5,   disdy_tria_c0>,
	 < -disdy_tria_c4,   disdy_tria_c5,  -disdy_tria_c0>,
	 < -disdy_tria_c4,  -disdy_tria_c5,   disdy_tria_c0>,
	 < -disdy_tria_c4,  -disdy_tria_c5,  -disdy_tria_c0>,
}
normalize(dirsDisdyTria)


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
normalize(dirsTriDipyra)


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
normalize(dirsPentDipyra)


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
normalize(dirsHexDipyra)


// Heptagonal Dipyramid
// Using dual Heptagonal Prism for axis system

// Heptagons are a mess so coordinates come from:
// (polroots(x^7 - 1) * I) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 7) + sin(2*Pi / 7)*I))
// Which is the roots of unity rotated 90 degrees and scaled to make edges length 1

#declare dirsHepDipyra = array [14] {
	 < 0.0,  0.5,  1.1523824354812432526205751117734275567>,
	 < 0.5,  0.5, -1.0382606982861682835817694307429201654>,
	 <-0.5,  0.5, -1.0382606982861682835817694307429201654>,
	 < 0.90096886790241912623610231950744505116,  0.5,  0.71849869636368513214480677892506880211>,
 	 <-0.90096886790241912623610231950744505116,  0.5,  0.71849869636368513214480677892506880211>,
	 < 1.1234898018587335305250048840042398106 ,  0.5, -0.25642921581813847487332490406886241512>,
 	 <-1.1234898018587335305250048840042398106 ,  0.5, -0.25642921581813847487332490406886241512>,
 	 < 0.0, -0.5,  1.1523824354812432526205751117734275567>,
	 < 0.5, -0.5, -1.0382606982861682835817694307429201654>,
	 <-0.5, -0.5, -1.0382606982861682835817694307429201654>,
	 < 0.90096886790241912623610231950744505116, -0.5,  0.71849869636368513214480677892506880211>,
 	 <-0.90096886790241912623610231950744505116, -0.5,  0.71849869636368513214480677892506880211>,
	 < 1.1234898018587335305250048840042398106 , -0.5, -0.25642921581813847487332490406886241512>,
 	 <-1.1234898018587335305250048840042398106 , -0.5, -0.25642921581813847487332490406886241512>,
}
normalize(dirsHepDipyra)


// Octagonal Dipyramid
// Using dual Octagonal Prism for axis system

// sqrt((1/2) * (2 + sqrt(2)))
#declare oct_dipyra_c0 = 1.3065629648763765278566431734271871536;

// sqrt(2 + sqrt(2)) / 2
#declare oct_dipyra_c1 = 0.92387953251128675612818318939678828682;

#declare dirsOctDipyra=array [16] {
	 <0.0,  0.5,  oct_dipyra_c0>,
 	 <0.0,  0.5, -oct_dipyra_c0>,
   	 < oct_dipyra_c1,  0.5,  oct_dipyra_c1>,
	 < oct_dipyra_c1,  0.5, -oct_dipyra_c1>,
   	 <-oct_dipyra_c1,  0.5,  oct_dipyra_c1>,
 	 <-oct_dipyra_c1,  0.5, -oct_dipyra_c1>,
	 < oct_dipyra_c0,  0.5, 0.0>
 	 <-oct_dipyra_c0,  0.5, 0.0>
 	 <0.0, -0.5,  oct_dipyra_c0>,
 	 <0.0, -0.5, -oct_dipyra_c0>,
   	 < oct_dipyra_c1, -0.5,  oct_dipyra_c1>,
	 < oct_dipyra_c1, -0.5, -oct_dipyra_c1>,
   	 <-oct_dipyra_c1, -0.5,  oct_dipyra_c1>,
 	 <-oct_dipyra_c1, -0.5, -oct_dipyra_c1>,
	 < oct_dipyra_c0, -0.5, 0.0>
 	 <-oct_dipyra_c0, -0.5, 0.0>
}
normalize(dirsOctDipyra)


// Tetragonal Trapezohedron
// Using dual geometry square antiprism for axes

// Top coords
// (polroots(x^4 - 1) * I) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 4) + sin(2*Pi / 4)*I))

// Bottom coords
// (polroots(x^4 - 1) * (cos((2 * Pi) / 8) + sin((2*Pi) / 8)*I)) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 4) + sin(2*Pi / 4)*I))


// h(n) = sqrt(1 - (1/4)*(1/cos(Pi / (2 * n)))^2) / 2 where n=4
#declare tetra_trapezo_h = 0.42044820762685727151556273811660744752;

// sqrt(2) / 2
#declare tetra_trapezo_c0 = 0.70710678118654752440084436210484903928;

#declare dirsTetraTrapezo = array [8] {
	 < 0.0,  tetra_trapezo_h,  tetra_trapezo_c0>,
	 < 0.0,  tetra_trapezo_h, -tetra_trapezo_c0>,
	 < tetra_trapezo_c0,  tetra_trapezo_h,  0.0>,
 	 <-tetra_trapezo_c0,  tetra_trapezo_h,  0.0>,
	 < 0.5, -tetra_trapezo_h, -0.5>,
	 <-0.5, -tetra_trapezo_h,  0.5>,
	 < 0.5, -tetra_trapezo_h,  0.5>,
 	 <-0.5, -tetra_trapezo_h, -0.5>,
}
normalize(dirsTetraTrapezo)


// Pentagonal Trapezohedron
// Using dual geometry pentagonal antiprism for axes

// Top coords
// (polroots(x^5 - 1) * I) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 5) + sin(2*Pi / 5)*I))

// Bottom coords
// (polroots(x^5 - 1) * I * (cos((2 * Pi) / 10) + sin((2*Pi) / 10)*I)) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 5) + sin(2*Pi / 5)*I))


// h(n) = sqrt(1 - (1/4)*(1/cos(Pi / (2 * n)))^2) / 2 where n = 5
#declare pent_trapezo_h = 0.42532540417601996609077024853150553612;

#declare dirsPentTrapezo = array [10] {
	 < 0.0,  pent_trapezo_h,  0.85065080835203993218154049706301107224>,
	 < 0.5,  pent_trapezo_h, -0.68819096023558676910360479095544383976>,
	 <-0.5,  pent_trapezo_h, -0.68819096023558676910360479095544383976>,
	 < 0.80901699437494742410229341718281905886,  pent_trapezo_h,  0.26286555605956680301283454242393830364>,
 	 <-0.80901699437494742410229341718281905886,  pent_trapezo_h,  0.26286555605956680301283454242393830364>,
	 <-0.5 , -pent_trapezo_h,  0.68819096023558676910360479095544383976>,
	 < 0.80901699437494742410229341718281905886, -pent_trapezo_h, -0.26286555605956680301283454242393830364>,
	 < 0.0, -pent_trapezo_h, -0.85065080835203993218154049706301107224>,
	 < 0.5, -pent_trapezo_h,  0.68819096023558676910360479095544383976>,
	 <-0.80901699437494742410229341718281905886, -pent_trapezo_h, -0.26286555605956680301283454242393830364>,
}
normalize(dirsPentTrapezo)


// Hexagonal Trapezohedron
// Using dual geometry hexagonal antiprism for axes

// Top coords
// (polroots(x^6 - 1) * I) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 6) + sin(2*Pi / 6)*I))

// Bottom coords
// (polroots(x^6 - 1) * I * (cos((2 * Pi) / 12) + sin((2*Pi) / 12)*I)) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 6) + sin(2*Pi / 6)*I))

// h(n) = sqrt(1 - (1/4)*(1/cos(Pi / (2 * n)))^2) / 2 where n = 6
#declare hex_trapezo_h = 0.42779983858367609648461788310558818792;

#declare dirsHexTrapezo = array [12] {
	 < 0.0,  hex_trapezo_h,  1.0>,
 	 < 0.0,  hex_trapezo_h, -1.0>,
	 < 0.86602540378443864676372317075293618348, hex_trapezo_h, -0.5>,
 	 <-0.86602540378443864676372317075293618348, hex_trapezo_h, -0.5>,
 	 < 0.86602540378443864676372317075293618348, hex_trapezo_h,  0.5>,
 	 <-0.86602540378443864676372317075293618348, hex_trapezo_h,  0.5>,
	 < 0.5, -hex_trapezo_h, -0.86602540378443864676372317075293618348>,
	 <-0.5, -hex_trapezo_h,  0.86602540378443864676372317075293618348>,
 	 < 1.0, -hex_trapezo_h,  0.0>,
 	 <-0.5, -hex_trapezo_h, -0.86602540378443864676372317075293618348>,
 	 < 0.5, -hex_trapezo_h,  0.86602540378443864676372317075293618348>,
 	 <-1.0, -hex_trapezo_h,  0.0>,
}
normalize(dirsHexTrapezo)


// Heptagonal Trapezohedron
// Using dual geometry heptagonal antiprism for axes

// Top coords
// (polroots(x^7 - 1) * I) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 7) + sin(2*Pi / 7)*I))

// Bottom coords
// (polroots(x^7 - 1) * I * (cos((2 * Pi) / 14) + sin((2*Pi) / 14)*I)) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 7) + sin(2*Pi / 7)*I))

// h(n) = sqrt(1 - (1/4)*(1/cos(Pi / (2 * n)))^2) / 2 where n = 7
#declare hept_trapezo_h = 0.42923659824727732620247761433595883913;

// for(i = 1, length(l), printf("< %f, hept_trapezo_h, %f>\n", real(l[i]), imag(l[i]));)

#declare dirsHeptTrapezo = array [14] {
	 < 0.0, hept_trapezo_h,  1.1523824354812432526205751117734275567>
	 < 0.5, hept_trapezo_h, -1.0382606982861682835817694307429201654>
	 <-0.5, hept_trapezo_h, -1.0382606982861682835817694307429201654>
	 < 0.90096886790241912623610231950744505116, hept_trapezo_h,  0.71849869636368513214480677892506880211>
	 <-0.90096886790241912623610231950744505116, hept_trapezo_h,  0.71849869636368513214480677892506880211>
	 < 1.1234898018587335305250048840042398106, hept_trapezo_h, -0.25642921581813847487332490406886241512>
	 <-1.1234898018587335305250048840042398106, hept_trapezo_h, -0.25642921581813847487332490406886241512>
	 <-0.5, -hept_trapezo_h, 1.0382606982861682835817694307429201654>
	 < 0.90096886790241912623610231950744505116, -hept_trapezo_h, -0.71849869636368513214480677892506880211>
	 < 0.0, -hept_trapezo_h, -1.1523824354812432526205751117734275567>
	 < 0.5, -hept_trapezo_h, 1.0382606982861682835817694307429201654>
	 <-1.1234898018587335305250048840042398106, -hept_trapezo_h, 0.25642921581813847487332490406886241512>
	 < 1.1234898018587335305250048840042398106, -hept_trapezo_h, 0.25642921581813847487332490406886241512>
	 <-0.90096886790241912623610231950744505116, -hept_trapezo_h, -0.71849869636368513214480677892506880211>
}
normalize(dirsHeptTrapezo)


// Octagonal Trapezohedron
// Using dual geometry octagonal antiprism for axes

// Top coords
// (polroots(x^8 - 1) * I) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 8) + sin(2*Pi / 8)*I))

// Bottom coords
// (polroots(x^8 - 1) * I * (cos((2 * Pi) / 16) + sin((2*Pi) / 16)*I)) / abs((cos(0) + sin(0)*I) - (cos(2*Pi / 8) + sin(2*Pi / 8)*I))

// h(n) = sqrt(1 - (1/4)*(1/cos(Pi / (2 * n)))^2) / 2 where n = 8
#declare oct_trapezo_h = 0.43014778493148578322115038800205284617;

// for(i = 1, length(l), printf("< %f, oct_trapezo_h, %f>\n", real(l[i]), imag(l[i]));)

#declare dirsOctTrapezo = array [16] {
	 < 0.0,  oct_trapezo_h, -1.3065629648763765278566431734271871536>
	 < 0.0,  oct_trapezo_h, 1.3065629648763765278566431734271871536>
	 < 0.92387953251128675612818318939678828682,  oct_trapezo_h, -0.92387953251128675612818318939678828682>
	 <-0.92387953251128675612818318939678828682,  oct_trapezo_h, -0.92387953251128675612818318939678828682>
	 < 0.92387953251128675612818318939678828682,  oct_trapezo_h, 0.92387953251128675612818318939678828682>
	 <-0.92387953251128675612818318939678828682,  oct_trapezo_h, 0.92387953251128675612818318939678828682>
	 < 1.3065629648763765278566431734271871536,  oct_trapezo_h, 0.0>
	 <-1.3065629648763765278566431734271871536,  oct_trapezo_h, 0.0>
	 < 0.5, -oct_trapezo_h, -1.2071067811865475244008443621048490393>
	 <-0.5, -oct_trapezo_h, 1.2071067811865475244008443621048490393>
	 < 1.2071067811865475244008443621048490393, -oct_trapezo_h, -0.5>
	 <-0.5, -oct_trapezo_h, -1.2071067811865475244008443621048490393>
	 < 0.5, -oct_trapezo_h, 1.2071067811865475244008443621048490393>
	 <-1.2071067811865475244008443621048490393, -oct_trapezo_h,  0.5>
	 < 1.2071067811865475244008443621048490393, -oct_trapezo_h,  0.5>
	 <-1.2071067811865475244008443621048490393, -oct_trapezo_h, -0.5>
}
normalize(dirsOctTrapezo)


// Trapezo-rhombic dodecahedron
// Using dual geometry Triangular orthobicupola for axes

// Coordinates from Wolfram Alpha "Triangular orthobicupola virtex coordinates"

// 1 / (2 * sqrt(3))
#declare trap_rhom_dod_c0 = 0.28867513459481288225457439025097872782;

// sqrt(2 / 3)
#declare trap_rhom_dod_c1 = 0.81649658092772603273242802490196379732;

// 1 / sqrt(3)
#declare trap_rhom_dod_c2 = 0.57735026918962576450914878050195745565;

// sqrt(3) / 2
#declare trap_rhom_dod_c3 = 0.86602540378443864676372317075293618347;

#declare dirsTrapRhomDod = array [12] {
	 < 0.0, 0.0, -1.0>,
	 < 0.0, 0.0,  1.0>,
	 <-trap_rhom_dod_c0, -trap_rhom_dod_c1, -0.5>,
	 <-trap_rhom_dod_c0,  trap_rhom_dod_c1, -0.5>,
	 <-trap_rhom_dod_c0, -trap_rhom_dod_c1,  0.5>,
 	 <-trap_rhom_dod_c0,  trap_rhom_dod_c1,  0.5>,
	 < trap_rhom_dod_c2, -trap_rhom_dod_c1,  0.0>,
	 < trap_rhom_dod_c2,  trap_rhom_dod_c1,  0.0>,
	 <-trap_rhom_dod_c3,  0.0, -0.5>,
 	 <-trap_rhom_dod_c3,  0.0,  0.5>,
  	 < trap_rhom_dod_c3,  0.0, -0.5>,
   	 < trap_rhom_dod_c3,  0.0,  0.5>,
}
normalize(dirsTrapRhomDod)


// Pseudo-deltoidal icositetrahedron
// Using dual geometry Elongated square gyrobicupola for axes

// Coordinates from Wolfram Alpha "Elongated square gyrobicupola vertex coordinates"

// (1 + sqrt(2))
#declare pseu_delt_icosi_c0 = 2.4142135623730950488016887242096980786;

// 2 / sqrt(2)
#declare pseu_delt_icosi_c1 = 1.4142135623730950488016887242096980786;

#declare dirsPseuDeltIcosi = array [24] {
	 <-1, -pseu_delt_icosi_c0, -1>, // r1
	 <-1, -pseu_delt_icosi_c0,  1>,
	 < 0,  pseu_delt_icosi_c0, -pseu_delt_icosi_c1>,
 	 < 0,  pseu_delt_icosi_c0,  pseu_delt_icosi_c1>, // r2
	 < 1, -pseu_delt_icosi_c0, -1>,
 	 < 1, -pseu_delt_icosi_c0,  1>,
	 <-pseu_delt_icosi_c1,  pseu_delt_icosi_c0,  0>, //r3
	 < pseu_delt_icosi_c1,  pseu_delt_icosi_c0,  0>,
	 < 1, -1,  pseu_delt_icosi_c0>,
	 < 1,  1,  pseu_delt_icosi_c0>, //r4
	 <-1, -1,  pseu_delt_icosi_c0>,
	 <-1,  1,  pseu_delt_icosi_c0>,
	 <-pseu_delt_icosi_c0, -1,  1>, //r5
	 <-pseu_delt_icosi_c0,  1,  1>,
	 <-pseu_delt_icosi_c0, -1, -1>,
	 <-pseu_delt_icosi_c0,  1, -1>, //r6
	 <-1, -1, -pseu_delt_icosi_c0>,
	 <-1,  1, -pseu_delt_icosi_c0>,
	 < 1, -1, -pseu_delt_icosi_c0>, //r7
	 < 1,  1, -pseu_delt_icosi_c0>,
	 < pseu_delt_icosi_c0, -1, -1>,
	 < pseu_delt_icosi_c0,  1, -1>, //r8
	 < pseu_delt_icosi_c0, -1,  1>,
	 < pseu_delt_icosi_c0,  1,  1>,
}
normalize(dirsPseuDeltIcosi)


// Trapezo-Rhombic Triacontahedron
// Using dual geometry Pentagonal orthobirotunda for axes

// Coordinates from Wolfram Alpha "Pentagonal orthobirotunda vertex coordinates"

#declare dirsTrapRhomTria = array [30] {
	 <0.00000000000000000000000000000000000000, 0.00000000000000000000000000000000000000, -1.6180339887498948482045868343656381177>,
	 <0.00000000000000000000000000000000000000, 0.00000000000000000000000000000000000000, 1.6180339887498948482045868343656381177>,
	 <-0.95105651629515357211643933337938214341, 0.00000000000000000000000000000000000000, -1.3090169943749474241022934171828190589>,
	 <-0.95105651629515357211643933337938214341, 0.00000000000000000000000000000000000000, 1.3090169943749474241022934171828190589>,
	 <0.95105651629515357211643933337938214341, 0.00000000000000000000000000000000000000, -1.3090169943749474241022934171828190589>,
	 <0.95105651629515357211643933337938214341, 0.00000000000000000000000000000000000000, 1.3090169943749474241022934171828190589>,
	 <-1.5388417685876267012851452880184549120, 0.00000000000000000000000000000000000000, -0.50000000000000000000000000000000000000>,
	 <-1.5388417685876267012851452880184549120, 0.00000000000000000000000000000000000000, 0.50000000000000000000000000000000000000>,
	 <1.5388417685876267012851452880184549120, 0.00000000000000000000000000000000000000, -0.50000000000000000000000000000000000000>,
	 <1.5388417685876267012851452880184549120, 0.00000000000000000000000000000000000000, 0.50000000000000000000000000000000000000>,
	 <1.3763819204711735382072095819108876795, -0.85065080835203993218154049706301107224, 0.00000000000000000000000000000000000000>,
	 <1.3763819204711735382072095819108876795, 0.85065080835203993218154049706301107224, 0.00000000000000000000000000000000000000>,
	 <0.42532540417601996609077024853150553612, -0.85065080835203993218154049706301107224, -1.3090169943749474241022934171828190589>,
	 <0.42532540417601996609077024853150553612, 0.85065080835203993218154049706301107224, -1.3090169943749474241022934171828190589>,
	 <0.42532540417601996609077024853150553612, -0.85065080835203993218154049706301107224, 1.3090169943749474241022934171828190589>,
	 <0.42532540417601996609077024853150553612, 0.85065080835203993218154049706301107224, 1.3090169943749474241022934171828190589>,
	 <-1.1135163644116067351943750394869493759, -0.85065080835203993218154049706301107224, -0.80901699437494742410229341718281905886>,
	 <-1.1135163644116067351943750394869493759, 0.85065080835203993218154049706301107224, -0.80901699437494742410229341718281905886>,
	 <-1.1135163644116067351943750394869493759, -0.85065080835203993218154049706301107224, 0.80901699437494742410229341718281905886>,
	 <-1.1135163644116067351943750394869493759, 0.85065080835203993218154049706301107224, 0.80901699437494742410229341718281905886>,
	 <-0.85065080835203993218154049706301107224, -1.3763819204711735382072095819108876795, 0.00000000000000000000000000000000000000>,
	 <-0.85065080835203993218154049706301107224, 1.3763819204711735382072095819108876795, 0.00000000000000000000000000000000000000>,
	 <-0.26286555605956680301283454242393830364, -1.3763819204711735382072095819108876795, -0.80901699437494742410229341718281905886>,
	 <-0.26286555605956680301283454242393830364, 1.3763819204711735382072095819108876795, -0.80901699437494742410229341718281905886>,
	 <-0.26286555605956680301283454242393830364, -1.3763819204711735382072095819108876795, 0.80901699437494742410229341718281905886>,
	 <-0.26286555605956680301283454242393830364, 1.3763819204711735382072095819108876795, 0.80901699437494742410229341718281905886>,
	 <0.68819096023558676910360479095544383976, -1.3763819204711735382072095819108876795, -0.50000000000000000000000000000000000000>,
	 <0.68819096023558676910360479095544383976, 1.3763819204711735382072095819108876795, -0.50000000000000000000000000000000000000>,
	 <0.68819096023558676910360479095544383976, -1.3763819204711735382072095819108876795, 0.50000000000000000000000000000000000000>,
	 <0.68819096023558676910360479095544383976, 1.3763819204711735382072095819108876795, 0.50000000000000000000000000000000000000>,
}
normalize(dirsTrapRhomTria)


// ============================= SHAPE ONLY ======================


// Triangular Prism

// Sides
// (polroots(x^3 - 1) * I)

// Solving for circumscribing radius ratio
// ? 1 / dist(plane_line_intersect([0, 0, 1], [0, 0, 1], [sin((2 * Pi) / 6), 0, cos((2 * Pi) / 6)], [0, 0, 0]) + [0, 1, 0], [0, 0, 0])
// %10 = 0.44721359549995793928183473374625524709

#declare dirsTriPrism = array [5] {
	 < 0,  1, 0>,
	 < 0, -1, 0>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
	 < -0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
}
normalize(dirsTriPrism)

#declare shTriPrism = 0;
intersect_shape(shTriPrism, dirsTriPrism)


// Pentagonal Prism

#declare dirsPentPrism = array [7] {
	 < 0,  1, 0>,
	 < 0, -1, 0>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.58778525229247312916870595463907276860,  0, -0.80901699437494742410229341718281905886>,
	 < -0.58778525229247312916870595463907276860,  0, -0.80901699437494742410229341718281905886>,
	 < 0.95105651629515357211643933337938214341,  0, 0.30901699437494742410229341718281905886>,
	 < -0.95105651629515357211643933337938214341,  0, 0.30901699437494742410229341718281905886>,
}
normalize(dirsPentPrism)

#declare shPentPrism = 0;
intersect_shape(shPentPrism, dirsPentPrism)


// Hexagonal Prism

#declare dirsHexPrism = array [8] {
	 < 0,  1, 0>,
	 < 0, -1, 0>,
	 < 0.00000000000000000000000000000000000000,  0, -1.0000000000000000000000000000000000000>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
	 < -0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
	 < 0.86602540378443864676372317075293618347,  0, 0.50000000000000000000000000000000000000>,
	 < -0.86602540378443864676372317075293618347,  0, 0.50000000000000000000000000000000000000>,
}
normalize(dirsHexPrism)

#declare shHexPrism = 0;
intersect_shape(shHexPrism, dirsHexPrism)


// Heptagonal Prism

#declare dirsHepPrism = array [9] {
	 < 0,  1, 0>,
	 < 0, -1, 0>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.43388373911755812047576833284835875461,  0, -0.90096886790241912623610231950744505116>,
	 < -0.43388373911755812047576833284835875461,  0, -0.90096886790241912623610231950744505116>,
	 < 0.78183148246802980870844452667405775023,  0, 0.62348980185873353052500488400423981063>,
	 < -0.78183148246802980870844452667405775023,  0, 0.62348980185873353052500488400423981063>,
	 < 0.97492791218182360701813168299393121723,  0, -0.22252093395631440428890256449679475947>,
	 < -0.97492791218182360701813168299393121723,  0, -0.22252093395631440428890256449679475947>,
}
normalize(dirsHepPrism)

#declare shHepPrism = 0;
intersect_shape(shHepPrism, dirsHepPrism)


// Octagonal Prism

#declare dirsOctPrism = array [10] {
	 < 0,  1, 0>,
	 < 0, -1, 0>,
	 < 0.00000000000000000000000000000000000000,  0, -1.0000000000000000000000000000000000000>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.70710678118654752440084436210484903928,  0, -0.70710678118654752440084436210484903928>,
	 < -0.70710678118654752440084436210484903928,  0, -0.70710678118654752440084436210484903928>,
	 < 0.70710678118654752440084436210484903928,  0, 0.70710678118654752440084436210484903928>,
	 < -0.70710678118654752440084436210484903928,  0, 0.70710678118654752440084436210484903928>,
	 < 1.0000000000000000000000000000000000000,  0, 0.00000000000000000000000000000000000000>,
	 < -1.0000000000000000000000000000000000000,  0, 0.00000000000000000000000000000000000000>,
}
normalize(dirsOctPrism)

#declare shOctPrism = 0;
intersect_shape(shOctPrism, dirsOctPrism)


// Truncated Cube

#declare shTruncCube = 0;
intersect_shape(shTruncCube, dirsCF)
intersect_shape_r(shTruncCube, dirsCC, 1)


// Truncated Dodecahedron

// All these faces are at a distance of 1 from the origin

#declare shTruncDod = 0;
intersect_shape(shTruncDod, dirsDF)
intersect_shape_r(shTruncDod, dirsDC, 1)


// Cuboctahedron

// (sqrt(6)/3) / (sqrt(2)/2)
#declare scale_cubocto = 1.1547005383792515290182975610039149113;

#declare shCubocto = 0;
intersect_shape(shCubocto, dirsCF)
intersect_shape_r(shCubocto, dirsCC, scale_cubocto)


// Icosidodecahedron

// ((3*sqrt(3)+sqrt(15))/6) / (sqrt(5*(5+2*sqrt(5)))/5)
#declare scale_icosidod = 1.0981854713951092345032267190375866707;

#declare shIcosidod = 0;
intersect_shape(shIcosidod, dirsDF)
intersect_shape_r(shIcosidod, dirsDC, scale_icosidod)


// Truncated Tetrahedron

// (5*sqrt(6)/12) / (sqrt(6)/4)
#declare scale_trunctet = 1.6666666666666666666666666666666666667;

#declare shTrunctet = 0;
intersect_shape(shTrunctet, dirsTC)
intersect_shape_r(shTrunctet, dirsCC, scale_trunctet)


// Truncated Octahedron

// (5*sqrt(6)/12) / (sqrt(6)/4)
#declare scale_truncoct = 1.1547005383792515290182975610039149113;

#declare shTruncoct = 0;
intersect_shape(shTruncoct, dirsCC)
intersect_shape_r(shTruncoct, dirsCF, scale_truncoct)


// Truncated Cube

// ((3*sqrt(3)+2*sqrt(6))/6) / ((1+sqrt(2))/2)
#declare scale_atrunccube = 1.1547005383792515290182975610039149113;

#declare shATrunccube = 0;
intersect_shape(shATrunccube, dirsCF)
intersect_shape_r(shATrunccube, dirsCC, scale_atrunccube)


// Rhombicuboctahedron

// ((3*sqrt(3)+sqrt(6))/6) / ((1+sqrt(2))/2)
#declare scale_rhomcuboct = 1.0556428926658263009557072693019701390;

#declare shRhomCubOct = 0;
intersect_shape(shRhomCubOct, dirsCF)
intersect_shape_r(shRhomCubOct, dirsCE, 1)
intersect_shape_r(shRhomCubOct, dirsCC, scale_rhomcuboct)


// Truncated Cuboctahedron

// ((sqrt(3)+sqrt(6))/2) / ((1+2*sqrt(2))/2)
#declare scale_trunccuboct_hex = 1.0922345950699728541113747284605012133;

// ((3+sqrt(2))/2) / ((1+2*sqrt(2))/2)
#declare scale_trunccuboct_square = 1.1530096874093536062869205172926414847;

#declare shTruncCubOct = 0;
intersect_shape(shTruncCubOct, dirsCF)
intersect_shape_r(shTruncCubOct, dirsCC, scale_trunccuboct_hex)
intersect_shape_r(shTruncCubOct, dirsCE, scale_trunccuboct_square)



// ============================= CUTS ONLY ======================

// Dihedral cuts
#declare dirsCutsDihe = array [2] {
	 <0,  1, 0>,
	 <0, -1, 0>,
}
normalize(dirsCutsDihe)


// Triangular Prism side faces

// Sides
// (polroots(x^3 - 1) * I)

#declare dirsCutsTriPrism = array [3] {
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
	 < -0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
}
normalize(dirsCutsTriPrism)


// Square Prism side faces

// Sides
// (polroots(x^4 - 1) * I)

#declare dirsCutsSquarePrism = array [4] {
	 < 0.00000000000000000000000000000000000000,  0, -1.0000000000000000000000000000000000000>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 1.0000000000000000000000000000000000000,  0, 0.00000000000000000000000000000000000000>,
	 < -1.0000000000000000000000000000000000000,  0, 0.00000000000000000000000000000000000000>,
}
normalize(dirsCutsSquarePrism)


// Pentagonal Prism side faces

// Sides
// (polroots(x^5 - 1) * I)

#declare dirsCutsPentPrism = array [5] {
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.58778525229247312916870595463907276860,  0, -0.80901699437494742410229341718281905886>,
	 < -0.58778525229247312916870595463907276860,  0, -0.80901699437494742410229341718281905886>,
	 < 0.95105651629515357211643933337938214341,  0, 0.30901699437494742410229341718281905886>,
	 < -0.95105651629515357211643933337938214341,  0, 0.30901699437494742410229341718281905886>,
}
normalize(dirsCutsPentPrism)


// Hexagonal Prism side faces

// Sides
// (polroots(x^6 - 1) * I)

#declare dirsCutsHexPrism = array [6] {
	 < 0.00000000000000000000000000000000000000,  0, -1.0000000000000000000000000000000000000>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
	 < -0.86602540378443864676372317075293618347,  0, -0.50000000000000000000000000000000000000>,
	 < 0.86602540378443864676372317075293618347,  0, 0.50000000000000000000000000000000000000>,
	 < -0.86602540378443864676372317075293618347,  0, 0.50000000000000000000000000000000000000>,
}
normalize(dirsCutsHexPrism)


// Heptagonal Prism side faces

// Sides
// (polroots(x^7 - 1) * I)

#declare dirsCutsHepPrism = array [7] {
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.43388373911755812047576833284835875461,  0, -0.90096886790241912623610231950744505116>,
	 < -0.43388373911755812047576833284835875461,  0, -0.90096886790241912623610231950744505116>,
	 < 0.78183148246802980870844452667405775023,  0, 0.62348980185873353052500488400423981063>,
	 < -0.78183148246802980870844452667405775023,  0, 0.62348980185873353052500488400423981063>,
	 < 0.97492791218182360701813168299393121723,  0, -0.22252093395631440428890256449679475947>,
	 < -0.97492791218182360701813168299393121723,  0, -0.22252093395631440428890256449679475947>,
}
normalize(dirsCutsHepPrism)


// Octagonal Prism side faces

// Sides
// (polroots(x^8 - 1) * I)

#declare dirsCutsOctPrism = array [8] {
	 < 0.00000000000000000000000000000000000000,  0, -1.0000000000000000000000000000000000000>,
	 < 0.00000000000000000000000000000000000000,  0, 1.0000000000000000000000000000000000000>,
	 < 0.70710678118654752440084436210484903928,  0, -0.70710678118654752440084436210484903928>,
	 < -0.70710678118654752440084436210484903928,  0, -0.70710678118654752440084436210484903928>,
	 < 0.70710678118654752440084436210484903928,  0, 0.70710678118654752440084436210484903928>,
	 < -0.70710678118654752440084436210484903928,  0, 0.70710678118654752440084436210484903928>,
	 < 1.0000000000000000000000000000000000000,  0, 0.00000000000000000000000000000000000000>,
	 < -1.0000000000000000000000000000000000000,  0, 0.00000000000000000000000000000000000000>,
}
normalize(dirsCutsOctPrism)


// Tetrahedron faces
#declare dirsTF=array [4] {
	 <-1,-1,-1>,<-1,1,1>,<1,-1,1>,<1,1,-1>
};
normalize(dirsTF)



// ============================= SHAPES ======================

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

// Disdyakis Triacontahedron
#declare shDisdyTria = 0;
intersect_shape(shDisdyTria, dirsDisdyTria)

// Triangular Dipyramid
#declare shTriDipyra = 0;
intersect_shape(shTriDipyra, dirsTriDipyra)

// Pentagonal Dipyramid
#declare shPentDipyra = 0;
intersect_shape(shPentDipyra, dirsPentDipyra)

// Hexagonal Dipyramid
#declare shHexDipyra = 0;
intersect_shape(shHexDipyra, dirsHexDipyra)

// Heptagonal Dipyramid
#declare shHepDipyra = 0;
intersect_shape(shHepDipyra, dirsHepDipyra)

// Octagonal Dipyramid
#declare shOctDipyra = 0;
intersect_shape(shOctDipyra, dirsOctDipyra)

// Tetragonal Trapezohedron
#declare shTetraTrapezo = 0;
intersect_shape(shTetraTrapezo, dirsTetraTrapezo)

// Pentagonal Trapezohedron
#declare shPentTrapezo = 0;
intersect_shape(shPentTrapezo, dirsPentTrapezo)

// Hexagonal Trapezohedron
#declare shHexTrapezo = 0;
intersect_shape(shHexTrapezo, dirsHexTrapezo)

// Heptagonal Trapezohedron
#declare shHeptTrapezo = 0;
intersect_shape(shHeptTrapezo, dirsHeptTrapezo)

// Octagonal Trapezohedron
#declare shOctTrapezo = 0;
intersect_shape(shOctTrapezo, dirsOctTrapezo)

// Trapezo-rhombic dodecahedron
#declare shTrapRhomDod = 0;
intersect_shape(shTrapRhomDod, dirsTrapRhomDod)

// Pseudo-deltoidal icositetrahedron
#declare shPseuDeltIcosi = 0;
intersect_shape(shPseuDeltIcosi, dirsPseuDeltIcosi)

// Trapezo-Rhombic Triacontahedron
#declare shTrapRhomTria = 0;
intersect_shape(shTrapRhomTria, dirsTrapRhomTria)
