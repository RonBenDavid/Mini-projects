function [ok] = image2excel(fname,matrix)
%Ron ben david
if(ischar(fname))
if isa(matrix,'uint8')
     if isfile(fname)
         fname=[fname(1:end-5),'New','.xlsx'];
     end
         if (ndims(matrix))==2
             xlswrite('Grayscale.xlsx',matrix);
         end
         if (ndims(matrix))==3
             xlswrite(fname,matrix(1:end,1:end,1),'red');
             xlswrite(fname,matrix(1:end,1:end,2),'blue');
             xlswrite(fname,matrix(1:end,1:end,3),'green');
         end
        ok=1;
    else
        ok=0;
end
end
end

