function [] = SaveDataStruct(struct,fname)
%Ron ben david
fname=append(fname,".xlsx");
cell=[string(struct.xName),string(struct.yName);(num2cell(struct.x))',(num2cell(struct.y))'];
xlswrite(fname,cell);
end

