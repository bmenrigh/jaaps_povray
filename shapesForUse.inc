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
//normalize all dirset- items
normalize(dirsTC)
normalize(dirsCF)
normalize(dirsCC)
normalize(dirsCE)
normalize(dirsDF)
normalize(dirsDC)
normalize(dirsDE)
normalize(dirsCW)
normalize(dirsDeltIcosi)

// ------------------------------------

//regular tetrahedron
#declare shTet=intersection{
    plane {-dirsTC[0],1}
    plane {-dirsTC[1],1}
    plane {-dirsTC[2],1}
    plane {-dirsTC[3],1}

}
//cube
#declare shCube=intersection{
    plane {dirsCF[0],1}
    plane {dirsCF[1],1}
    plane {dirsCF[2],1}
    plane {dirsCF[3],1}
    plane {dirsCF[4],1}
    plane {dirsCF[5],1}
}
//regular octahedron
#declare shOct=intersection{
    plane {dirsCC[0],1}
    plane {dirsCC[1],1}
    plane {dirsCC[2],1}
    plane {dirsCC[3],1}
    plane {dirsCC[4],1}
    plane {dirsCC[5],1}
    plane {dirsCC[6],1}
    plane {dirsCC[7],1}
}
//rhombic dodecahedron
#declare shRhDod=intersection{
    plane {dirsCE[ 0],1}
    plane {dirsCE[ 1],1}
    plane {dirsCE[ 2],1}
    plane {dirsCE[ 3],1}
    plane {dirsCE[ 4],1}
    plane {dirsCE[ 5],1}
    plane {dirsCE[ 6],1}
    plane {dirsCE[ 7],1}
    plane {dirsCE[ 8],1}
    plane {dirsCE[ 9],1}
    plane {dirsCE[10],1}
    plane {dirsCE[11],1}
}
//regular dodecahedron
#declare shDod=intersection{
    plane {dirsDF[ 0],1}
    plane {dirsDF[ 1],1}
    plane {dirsDF[ 2],1}
    plane {dirsDF[ 3],1}
    plane {dirsDF[ 4],1}
    plane {dirsDF[ 5],1}
    plane {dirsDF[ 6],1}
    plane {dirsDF[ 7],1}
    plane {dirsDF[ 8],1}
    plane {dirsDF[ 9],1}
    plane {dirsDF[10],1}
    plane {dirsDF[11],1}

}
//regular icosahedron
#declare shIco=intersection{
    plane {dirsDC[ 0],1}
    plane {dirsDC[ 1],1}
    plane {dirsDC[ 2],1}
    plane {dirsDC[ 3],1}
    plane {dirsDC[ 4],1}
    plane {dirsDC[ 5],1}
    plane {dirsDC[ 6],1}
    plane {dirsDC[ 7],1}
    plane {dirsDC[ 8],1}
    plane {dirsDC[ 9],1}
    plane {dirsDC[10],1}
    plane {dirsDC[11],1}
    plane {dirsDC[12],1}
    plane {dirsDC[13],1}
    plane {dirsDC[14],1}
    plane {dirsDC[15],1}
    plane {dirsDC[16],1}
    plane {dirsDC[17],1}
    plane {dirsDC[18],1}
    plane {dirsDC[19],1}
}

//rhombic triacontahedron
#declare shRhTriacon=intersection{
    plane {dirsDE[ 0],1}
    plane {dirsDE[ 1],1}
    plane {dirsDE[ 2],1}
    plane {dirsDE[ 3],1}
    plane {dirsDE[ 4],1}
    plane {dirsDE[ 5],1}
    plane {dirsDE[ 6],1}
    plane {dirsDE[ 7],1}
    plane {dirsDE[ 8],1}
    plane {dirsDE[ 9],1}
    plane {dirsDE[10],1}
    plane {dirsDE[11],1}
    plane {dirsDE[12],1}
    plane {dirsDE[13],1}
    plane {dirsDE[14],1}
    plane {dirsDE[15],1}
    plane {dirsDE[16],1}
    plane {dirsDE[17],1}
    plane {dirsDE[18],1}
    plane {dirsDE[19],1}
    plane {dirsDE[20],1}
    plane {dirsDE[21],1}
    plane {dirsDE[22],1}
    plane {dirsDE[23],1}
    plane {dirsDE[24],1}
    plane {dirsDE[25],1}
    plane {dirsDE[26],1}
    plane {dirsDE[27],1}
    plane {dirsDE[28],1}
    plane {dirsDE[29],1}
}

//triakis octahedron
#declare shCW=intersection{
    plane {dirsCW[ 0],1}
    plane {dirsCW[ 1],1}
    plane {dirsCW[ 2],1}
    plane {dirsCW[ 3],1}
    plane {dirsCW[ 4],1}
    plane {dirsCW[ 5],1}
    plane {dirsCW[ 6],1}
    plane {dirsCW[ 7],1}
    plane {dirsCW[ 8],1}
    plane {dirsCW[ 9],1}
    plane {dirsCW[10],1}
    plane {dirsCW[11],1}
    plane {dirsCW[12],1}
    plane {dirsCW[13],1}
    plane {dirsCW[14],1}
    plane {dirsCW[15],1}
    plane {dirsCW[16],1}
    plane {dirsCW[17],1}
    plane {dirsCW[18],1}
    plane {dirsCW[19],1}
    plane {dirsCW[20],1}
    plane {dirsCW[21],1}
    plane {dirsCW[22],1}
    plane {dirsCW[23],1}
}

// Deltoidal Icositetrahedron
#declare shDeltIcosi = intersection {
    plane {dirsDeltIcosi[ 0],1}
    plane {dirsDeltIcosi[ 1],1}
    plane {dirsDeltIcosi[ 2],1}
    plane {dirsDeltIcosi[ 3],1}
    plane {dirsDeltIcosi[ 4],1}
    plane {dirsDeltIcosi[ 5],1}
    plane {dirsDeltIcosi[ 6],1}
    plane {dirsDeltIcosi[ 7],1}
    plane {dirsDeltIcosi[ 8],1}
    plane {dirsDeltIcosi[ 9],1}
    plane {dirsDeltIcosi[10],1}
    plane {dirsDeltIcosi[11],1}
    plane {dirsDeltIcosi[12],1}
    plane {dirsDeltIcosi[13],1}
    plane {dirsDeltIcosi[14],1}
    plane {dirsDeltIcosi[15],1}
    plane {dirsDeltIcosi[16],1}
    plane {dirsDeltIcosi[17],1}
    plane {dirsDeltIcosi[18],1}
    plane {dirsDeltIcosi[19],1}
    plane {dirsDeltIcosi[20],1}
    plane {dirsDeltIcosi[21],1}
    plane {dirsDeltIcosi[22],1}
    plane {dirsDeltIcosi[23],1}
}
