program BadNested;

begin
    repeat
        begin
            writeln('Inside begin');
        until i > 10;
    end;
end.
