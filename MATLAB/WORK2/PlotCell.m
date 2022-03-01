function [] = PlotCell(cellarray,dimension)
%Ron ben david
switch dimension
    case '2D'
        subplot(1,2,1);
        plot(cellarray{3},cellarray{5});
        xlabel(cellarray{4});
        ylabel(cellarray{6});
        
        subplot(1,2,2);
        plot(cellarray{1},cellarray{5});
        xlabel(cellarray{2});
        ylabel(cellarray{6});
        
    case '3D'
        plot3(cellarray{1},cellarray{3},cellarray{5});
        title('3D');
    case 'all'
        subplot(2,2,1);
        plot(cellarray{3},cellarray{5});
        xlabel(cellarray{4});
        ylabel(cellarray{6});
        subplot(2,2,2);
        plot(cellarray{1},cellarray{5});
        xlabel(cellarray{2});
        ylabel(cellarray{6});
        subplot(2,2,[3,4]);
        plot3(cellarray{1},cellarray{3},cellarray{5});
        title('3D');
    otherwise
        disp('the char array is not correct!')
end
end

