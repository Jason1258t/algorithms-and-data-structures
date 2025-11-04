program ComplexTest;

begin
    { begin in comment should be ignored }
    repeat
        begin
            // end in comment should be ignored
            writeln('REPEAT and BEGIN nesting test');
        end;
    until false;
end.
