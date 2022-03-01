function [matrix] = RedLineDrawer(matrix,number)
%Ron ben david
w=(length(matrix(1:end,1,1)));
if (ndims(matrix)==3)
if isnumeric(number)
    if number<0
    number=2;
    end
    if (mod(number,2)==1)
    number=number+1;
    end
    if(number>(w))
    number=round((w)*0.5);
    end
d=(w*0.5);
wd=(w*0.5)-(number*0.5);
wf=(w*0.5)+(number*0.5);
matrix(1:end,wd:wf,1)=255;
matrix(1:end,wd:wf,2)=0;
matrix(1:end,wd:wf,3)=0;
end
else
matrix=[];
end
end

