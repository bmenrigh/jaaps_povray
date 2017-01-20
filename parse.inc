
#version 3.6;

#macro findNext(
		String, 		//a string
		Character, 		//char to search for (string with length 1)
		start)			//integer: start looking from

	#local len = strlen (String);
	#local Char= substr (Character,1,1);
	#local foundat=-1;
	//count Character's occurances in String
	#local Count = start;
	#while (Count<len)
		#local Charcmp=substr(String,Count+1,1)
		#if(!strcmp(Char,Charcmp))
			#local foundat=Count;
			#local Count = len;
		#end
	#local Count = Count + 1;
	#end
	foundat

#end

#macro countocc(
	String,
	Character)
	#local Char= substr (Character,1,1);
	#local occ=0;

	#local Count = 0;
	#while ( Count < strlen (String))
		#local Charcmp=substr(String,Count+1,1)
		#if(!strcmp(Char,Charcmp))
			#local occ=occ+1;
		#end
	#local Count=Count+1;
	#end

	occ
#end

#macro split (// splits 'String' by means of 'Character'
	String,
	Character)
	#local Char= substr (Character,1,1);
	#local occ = countocc(String,Character);
	#local strArray = array[occ+1]
	#local integers = array[occ+2]
	#local integers[0]=-1;
	#local integers[occ+1]=strlen(String);

	#local ff=-1;		//first occ found at
	#local lf=0;		//look from
	#local Count = 1;
	#while (Count < occ+1 )
		#local ff= findNext ( String, Char , lf );
		#local integers[Count]=ff;

		#local lf = ff+1;

	#local Count = Count +1;
	#end


	#local Count = 0;
	#while (Count < occ+1 )
		#local strArray[Count]=substr(String, integers[Count]+2, integers[Count+1] - integers[Count] -1)

	#local Count = Count +1;
	#end
	strArray

#end



#declare _angle=array[3]





#macro parse(paramstring)

	#local sliderTable=array [4][5]{

	    //the columns 2 to 5 stand for the slider values (300-0), -1 mean 'not in use'
	    {1,-1,-1,-1,-1,},
	    {1,-1,-1,-1,-1,},
	    {1,-1,-1,-1,-1,},
	    {1,-1,-1,-1,-1,},
	}

	#if (strlen(paramstring)>0)
		#local urlquery=split(paramstring,"?")
		#local pstr = urlquery[dimension_size(urlquery,1)-1]
		#local urlterms =split(pstr,"&")
		#local Count=0;
		#while (Count < dimension_size ( urlterms,1))
			#local pdef= split(urlterms[Count],"=")
			#local param=pdef[0]
			#local pval=pdef[1]
			#local pval_ = split (pval,",")
			#local pvals = array [dimension_size ( pval_,1)]

			#local Count_=0;
			#while (Count_ < dimension_size ( pval_,1))
				#local pvals[Count_]=val(pval_[Count_]);
			#local Count_= Count_ + 1;
			#end
			#if	(!strcmp ("symred",param))
				#declare sliderTable [0][0]=val(pval);
			#end
			#if	(!strcmp ("symgreen",param))
				#declare sliderTable [1][0]=val(pval);
			#end
			#if	(!strcmp ("symblue",param))
				#declare sliderTable [2][0]=val(pval);
			#end
			#if	(!strcmp ("symyellow",param))
				#declare sliderTable [3][0]=val(pval);
			#end

			#if	(!strcmp ("red",param))
				#local Count_=0;
				#while (Count_ < dimension_size ( pvals,1))
					#declare sliderTable[0][Count_+1]=pvals[Count_];
				#local Count_= Count_ + 1;
				#end
			#end
			#if	(!strcmp ("green",param))
				#local Count_=0;
				#while (Count_ < dimension_size ( pvals,1))
					#declare sliderTable[1][Count_+1]=pvals[Count_];
				#local Count_= Count_ + 1;
				#end
			#end
			#if	(!strcmp ("blue",param))
				#local Count_=0;
				#while (Count_ < dimension_size ( pvals,1))
					#declare sliderTable[2][Count_+1]=pvals[Count_];
				#local Count_= Count_ + 1;
				#end
			#end
			#if	(!strcmp ("yellow",param))
				#local Count_=0;
				#while (Count_ < dimension_size ( pvals,1))
					#declare sliderTable[3][Count_+1]=pvals[Count_];
				#local Count_= Count_ + 1;
				#end
			#end
			#if	(!strcmp ("angle",param))
				#local Count_=0;
				#while (Count_ < dimension_size ( pvals,1))
					#declare _angle[Count_]=pvals[Count_];
				#local Count_= Count_ + 1;
				#end
				#declare _angle[1] = _angle[1] -90;//
			#end

		#local Count= Count + 1;
		#end



	#end


	sliderTable

#end
