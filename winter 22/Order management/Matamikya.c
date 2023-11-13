#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Matamikya.h"
#include "set.h"
#include "Product.h"
#include "Order.h"
#include "Print.h"

#define ERROR_RANGE 0.001
#define HALF_AMOUNT 0.5

struct Matamikya_t {
	Set Products;
	Set orders;
};

Matamikya matamikyaCreate()
{
	Matamikya new_matamikya = malloc(sizeof(*new_matamikya));
	if (new_matamikya == NULL) {
		return NULL;
	}

	new_matamikya->Products = setCreate(productCopy,
										productFree,
										productCompare);
	if (new_matamikya->Products == NULL) {
		free(new_matamikya);
		return NULL;
	}

	new_matamikya->orders = setCreate(orderCopy,
									  orderFree,
									  orderCompare);
	if (new_matamikya->orders == NULL) {
		setDestroy(new_matamikya->Products);
		free(new_matamikya);
		return NULL;
	}

	return new_matamikya;
}

void matamikyaDestroy(Matamikya matamikya)
{
	if (matamikya == NULL) {
		return;
	}
	setDestroy(matamikya->Products);
	setDestroy(matamikya->orders);
	free(matamikya);
}

static bool isTheNameLegal(const char* name)
{
	if (strlen(name) == 0) {
		return false;
	}
	int index = 0;
	while (name[index]) {
		if (!(('a' <= name[index] && name[index] <= 'z') || ('A' <= name[index] && name[index] <= 'Z') ||
			  ('0' <= name[index] && name[index] <= '9') || (name[index] == ' '))) {
			return false;
		}
		index++;
	}
	return true;
}

static bool isTheAmountTypeLegal(const double amount, const MatamikyaAmountType amountType)
{
	if (amountType == -1) {
		return false;
	}

	if (amountType == MATAMIKYA_INTEGER_AMOUNT) {
		if (fabs(amount - round(amount)) > ERROR_RANGE) {
			return false;
		}
		return true;
	}

	if (amountType == MATAMIKYA_HALF_INTEGER_AMOUNT) {
		if (fabs(amount - round(amount)) <= ERROR_RANGE) {
			return true;
		}
		if (fabs(amount + HALF_AMOUNT - round(amount + HALF_AMOUNT)) <= ERROR_RANGE) {
			return true;
		}
		return false;
	}

	return true;
}

static bool isProductIsInByID(Set products, unsigned int id)
{
	SET_FOREACH(Product, iterator, products) {
		if (getProductID(iterator) == id) {
			return true;
		}
	}
	return false;
}

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char* name,
							  const double amount, const MatamikyaAmountType amountType,
							  const MtmProductData customData, MtmCopyData copyData,
							  MtmFreeData freeData, MtmGetProductPrice prodPrice)
{
	if (matamikya == NULL || name == NULL || customData == NULL ||
		copyData == NULL || freeData == NULL || prodPrice == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}
	if (!isTheNameLegal(name)) {
		return MATAMIKYA_INVALID_NAME;
	}

	if (amount < 0 || !isTheAmountTypeLegal(amount, amountType)) {
		return MATAMIKYA_INVALID_AMOUNT;
	}

	if (isProductIsInByID(matamikya->Products, id)) {
		return MATAMIKYA_PRODUCT_ALREADY_EXIST;
	}


	Product new_product = productCreat(name, id, amount, amountType,
									   customData, copyData, freeData, prodPrice);
	if (new_product == NULL) {
		return MATAMIKYA_OUT_OF_MEMORY;
	}

	if (setAdd(matamikya->Products, new_product) != SET_SUCCESS) {
		productFree(new_product);
		return MATAMIKYA_OUT_OF_MEMORY;
	}

	productFree(new_product);
	return MATAMIKYA_SUCCESS;
}

static Product getProductByID(Set products, unsigned int id)
{
	SET_FOREACH(Product, product, products) {
		if (compareProductID(product, id)) {
			return product;
		}
	}
	return NULL;
}


static Order getOrderByID(Set orders, unsigned int id)
{
	if (orders == NULL) {
		return NULL;
	}
	SET_FOREACH(Order, order, orders) {
		unsigned int order_id = getOrderID(order);
		if (orderCompare(&order_id, &id) == 0) {
			return order;
		}
	}
	return NULL;
}

MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount)
{
	if (matamikya == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}

	Product product = getProductByID(matamikya->Products, id);
	if (product == NULL) {
		return MATAMIKYA_PRODUCT_NOT_EXIST;
	}
	if (!isTheAmountTypeLegal(amount, getProductAmountType(product))) {
		return MATAMIKYA_INVALID_AMOUNT;
	}

	double total_amount = getProductAmount(product) + amount;
	if (!isTheAmountTypeLegal(total_amount, getProductAmountType(product))) {
		return MATAMIKYA_INVALID_AMOUNT;
	}
	if (total_amount < 0) {
		return MATAMIKYA_INSUFFICIENT_AMOUNT;
	}
	setProductAmount(product, total_amount);
	return MATAMIKYA_SUCCESS;
}

static void removeProductFromOrdersByID(Set orders, unsigned int id)
{
	if (orders == NULL) {
		return;
	}
	SET_FOREACH(Order, order, orders) {
		removeOrderProductByID(order, id);
	}
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id)
{
	if (matamikya == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}
	Product product = getProductByID(matamikya->Products, id);
	if (product == NULL) {
		return MATAMIKYA_PRODUCT_NOT_EXIST;
	}

	setRemove(matamikya->Products, product);
	removeProductFromOrdersByID(matamikya->orders, id);
	return MATAMIKYA_SUCCESS;
}

static unsigned int getMaxOrderID(Set orders)
{
	if (orders == NULL) {
		return 0;
	}
	unsigned int max_order_id = getOrderID(setGetFirst(orders));
	SET_FOREACH(Order, iterator, orders) {
		if (max_order_id < getOrderID(iterator)) {
			max_order_id = getOrderID(iterator);
		}
	}
	return max_order_id;
}

unsigned int mtmCreateNewOrder(Matamikya matamikya)
{
	if (matamikya == NULL) {
		return 0;
	}
	Order new_order = orderCreat(1);
	if (new_order == NULL) {
		return 0;
	}

	setOrderID(new_order, getMaxOrderID(matamikya->orders) + 1);
	if (setAdd(matamikya->orders, new_order) != SET_SUCCESS) {
		orderFree(new_order);
		return 0;
	}
	unsigned int order_id = getOrderID(new_order);
	orderFree(new_order);
	return order_id;
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
											  const unsigned int productId, const double amount)
{
	if (matamikya == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}

	Product product_of_warehouse = getProductByID(matamikya->Products, productId);
	if (product_of_warehouse == NULL) {
		return MATAMIKYA_PRODUCT_NOT_EXIST;
	}
	if (!isTheAmountTypeLegal(amount, getProductAmountType(product_of_warehouse))) {
		return MATAMIKYA_INVALID_AMOUNT;
	}

	Order order = getOrderByID(matamikya->orders, orderId);
	if (order == NULL) {
		return MATAMIKYA_ORDER_NOT_EXIST;
	}

	Set products_of_order = getOrderProducts(order);
	if (!isProductIsInByID(products_of_order, productId)) {
		if (amount > 0) {
			if (setAdd(products_of_order, product_of_warehouse) != SET_SUCCESS) {
				return MATAMIKYA_OUT_OF_MEMORY;
			}
			setProductAmount(getProductByID(products_of_order, productId), amount);
		}
	} else {
		Product product_of_order = getProductByID(products_of_order, productId);
		if (getProductAmount(product_of_order) + amount <= 0) {
			removeOrderProductByID(order, productId);
			return MATAMIKYA_SUCCESS;
		} else {
			setProductAmount(product_of_order, amount);
		}
	}
	return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)
{
	if (matamikya == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}

	Order order = getOrderByID(matamikya->orders, orderId);
	if (order == NULL) {
		return MATAMIKYA_ORDER_NOT_EXIST;
	}
	Set products_of_order = getOrderProducts(order);
	SET_FOREACH(Product, product_in_order, products_of_order) {
		Product product_in_warehouse = getProductByID(matamikya->Products, getProductID(product_in_order));
		if (getProductAmount(product_in_warehouse) - getProductAmount(product_in_order) < 0) {
			return MATAMIKYA_INSUFFICIENT_AMOUNT;
		}
	}

	SET_FOREACH(Product, product_in_order, products_of_order) {
		double amount_product = getProductAmount(product_in_order);
		Product product_in_warehouse = getProductByID(matamikya->Products, getProductID(product_in_order));
		addProductAmount(product_in_warehouse, -amount_product);
		setProductTotalInCome(product_in_warehouse, amount_product);
	}

	setRemove(matamikya->orders, order);
	return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId)
{
	if (matamikya == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}
	Order order = getOrderByID(matamikya->orders, orderId);
	if (order == NULL) {
		return MATAMIKYA_ORDER_NOT_EXIST;
	}
	setRemove(matamikya->orders, order);
	return MATAMIKYA_SUCCESS;
}

static Product getFirstSmallProduct(Set products)
{
	if (products == NULL) {
		return NULL;
	}
	unsigned int min_product_id = getProductID(setGetFirst(products));
	SET_FOREACH(Product, iterator, products) {
		if (getProductID(iterator) < min_product_id) {
			min_product_id = getProductID(iterator);
		}
	}
	return getProductByID(products, min_product_id);
}

static Product getNextSmallProduct(Set products, unsigned int min_product_ID)
{
	if (products == NULL) {
		return NULL;
	}
	unsigned int next_product_min_id = min_product_ID;
	SET_FOREACH(Product, product, products) {
		if (min_product_ID < getProductID(product)) {
			next_product_min_id = getProductID(product);
			break;
		}
	}
	if (min_product_ID == next_product_min_id) {
		return NULL;
	}
	SET_FOREACH(Product, product, products) {
		if (min_product_ID < getProductID(product) && getProductID(product) < next_product_min_id) {
			next_product_min_id = getProductID(product);
		}
	}
	return getProductByID(products, next_product_min_id);
}

MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE* output)
{
	if (matamikya == NULL || matamikya->Products == NULL || output == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}
	fprintf(output, "Inventory Status:\n");

	for (Product product = getFirstSmallProduct(matamikya->Products); product != NULL;
		 product = getNextSmallProduct(matamikya->Products, getProductID(product))) {
		mtmPrintProductDetails(getProductName(product), getProductID(product),
							   getProductAmount(product), getProductPriceOneUnit(product), output);
	}
	return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE* output)
{
	if (matamikya == NULL || output == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}
	Order order = getOrderByID(matamikya->orders, orderId);
	if (order == NULL) {
		return MATAMIKYA_ORDER_NOT_EXIST;
	}
	mtmPrintOrderHeading(orderId, output);

	Set products_of_order = getOrderProducts(order);
	for (Product product = getFirstSmallProduct(products_of_order); product != NULL;
		 product = getNextSmallProduct(products_of_order, getProductID(product))) {
		mtmPrintProductDetails(getProductName(product), getProductID(product),
							   getProductAmount(product), getProductTotalPrice(product), output);
	}
	mtmPrintOrderSummary(getOrderProfits(order), output);
	return MATAMIKYA_SUCCESS;
}

static double maximumInCome(Set products)
{
	double max = 0;
	for (Product product = setGetFirst(products); product != NULL; product = setGetNext(products)) {
		if (getProductTotalInCome(product) > max) {
			max = getProductTotalInCome(product);
		}
	}
	return max;
}

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE* output)
{
	if (matamikya == NULL || matamikya->Products == NULL || output == NULL) {
		return MATAMIKYA_NULL_ARGUMENT;
	}
	double max_in_come = maximumInCome(matamikya->Products);
	fprintf(output, "Best Selling Product:\n");
	if (max_in_come == 0) {
		fprintf(output, "none\n");
		return MATAMIKYA_SUCCESS;
	}
	for (Product product = getFirstSmallProduct(matamikya->Products); product != NULL;
		 product = getNextSmallProduct(matamikya->Products, getProductID(product))) {
		if (getProductTotalInCome(product) == max_in_come) {
			mtmPrintIncomeLine(getProductName(product), getProductID(product), getProductTotalInCome(product),
							   output);
			break;
		}
	}
	return MATAMIKYA_SUCCESS;
}
