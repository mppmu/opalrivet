void FoldGraph(TGraphAsymmErrors* A, int N);


void ScaleGraph(TGraphAsymmErrors* A, double k,int scaleopt=0);




TGraphAsymmErrors* AddGraphs(double w1,double w2,TGraphAsymmErrors* A, TGraphAsymmErrors* B, TGraphAsymmErrors* D=NULL);


TGraphAsymmErrors* DivideGraphs(TGraphAsymmErrors* A, TGraphAsymmErrors* B, TGraphAsymmErrors* D=NULL,double toll=1.E-15);

