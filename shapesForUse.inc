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

#declare shDeltIcosi = 0;
intersect_shape(shDeltIcosi, dirsDeltIcosi)
