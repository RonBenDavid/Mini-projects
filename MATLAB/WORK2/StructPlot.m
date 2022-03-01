function [] = StructPlot(struct,char)
%Ron ben david
        plot(struct.x,struct.y,char);
        axis tight;
        xlabel(struct.xName);
        ylabel(struct.yName);
end

