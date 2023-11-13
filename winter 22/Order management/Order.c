#include "Order.h"
#include "Product.h"
#include <stdlib.h>

struct order_t {
	unsigned int orderId;
	Set products;
};


void* orderCopy(void* element)
{
	if (element == NULL) {
		return NULL;
	}
	Order order = element;
	Order new_order = orderCreat(order->orderId);
	if (new_order == NULL) {
		return NULL;
	}
	SET_FOREACH(Product, i, order->products) {
		if (setAdd(new_order->products, i) != SET_SUCCESS) {
			orderFree(new_order);
			return NULL;
		}
	}
	return new_order;
}

void orderFree(void* element)
{
	if (element == NULL) {
		return;
	}
	Order order = element;
	setDestroy(order->products);
	free(order);
}

int orderCompare(void* first_element, void* second_element)
{
	if (first_element == NULL || second_element == NULL) {
		return 0;
	}
	Order first_order = first_element;
	Order second_order = second_element;
	if (first_order->orderId == second_order->orderId) {
		return 0;
	}
	if (first_order->orderId > second_order->orderId) {
		return 1;
	} else {
		return -1;
	}
}

Order orderCreat(unsigned int orderId)
{

	Order new_order = malloc(sizeof(*new_order));
	if (new_order == NULL) {
		return NULL;
	}
	new_order->orderId = orderId;
	new_order->products = setCreate(productCopy, productFree, productCompare);
	if (new_order->products == NULL) {
		free(new_order);
		return NULL;
	}
	return new_order;
}

unsigned int getOrderID(Order order)
{
	if (order == NULL) {
		return 0;
	}
	return order->orderId;
}

Set getOrderProducts(Order order)
{
	if (order == NULL) {
		return NULL;
	}
	return order->products;
}

double getOrderProfits(Order order)
{
	if (order == NULL) {
		return 0;
	}
	double total_profit_of_order = 0;
	SET_FOREACH(Product, product, order->products) {
		total_profit_of_order += getProductTotalPrice(product);
	}
	return total_profit_of_order;
}

void setOrderID(Order order, unsigned int orderId)
{
	if (order == NULL) {
		return;
	}
	order->orderId = orderId;
}

void removeOrderProductByID(Order order, unsigned int productId)
{
	SET_FOREACH(Product, product, order->products) {
		if (getProductID(product) == productId) {
			setRemove(order->products, product);
			return;
		}
	}
}
