program TestComments;

begin
    writeln('begin until end');  { Это комментарий с until }
    // repeat until end;
    repeat
        writeln('Still inside repeat');
    until true;
end.
