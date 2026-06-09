   for(int i=sz(s)-1;i>=0;i--) {
            if(cur && res[i]=='(') {
                res[i]=')';
                cur-=2;
                cnt+=2;
            }
     