`timescale 1ns/1ps
module booth(in_a, in_b, sign, clk, rst, Product, Product_Valid);
input[31:0] in_a;
input[31:0] in_b;
input sign;
input flag;
input clk;
input rst;
output reg [63:0] Product;
output reg Product_Valid;

reg [6:0] Counter;
reg signed [63:0] Q;
reg signed [31:0] M;
reg Q_1;

always @(posedge clk or posedge rst)
begin
	if(rst)
		Counter <=6'b0;
	else
		Counter <= Counter +6'b1;
end

always @(posedge clk or posedge rst)
begin
		if(rst) begin
			Q<=64'b0;
			M<=32'b0;
			Q_1<=1'b0;
			Product<=64'd0;
		end
		else if(Counter==6'd0) begin
			if(in_a == 0 || in_b == 0)
				Product<=64'd0;
		end
end

always @(posedge clk or posedge rst)
begin
		if(rst) begin
			Q<=64'b0;
			M<=32'b0;
			Q_1<=1'b0;
			Product<=64'd0;
		end
		
		else if(Counter==6'd0) begin
			if(sign==1'b1) begin 
				Q<={32'b11111111111111111111111111111111, in_a};
			end
			else begin 
				Q<={32'b0, in_a};
			end	
			M <= in_b;
		end
		else if(Counter<=6'd32) begin
			if(M[0]==1'b1 && Q_1==1'b0)
					Product <= (~Q) + Product+1;
			else if(M[0]==1'b0 && Q_1==1'b1)
					Product <= Q+Product;
			M <= (M >> 1);
			Q <= (Q<<1);
			Q_1 <= M[0];
		end
end

always @(posedge clk or posedge rst)
begin
	if(rst)
		Product_Valid <=1'b0;
	else if(Counter==6'd32)
		Product_Valid <=1'b1;
	else
		Product_Valid <=1'b0;
end
endmodule