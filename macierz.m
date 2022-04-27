a = -100;
b = 100;
A = (b-a).*randn(1000,1000) + a;
for i=1:1000
    for j=1:1000
        if j==i
            A(i,j)=0;
        end
    end
end

A = round(A);
[n,m]=size(A);
B=A'+A;
B(1:n+1:end)=diag(A);
histogram(B);
