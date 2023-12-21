// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

contract Marketplace {
	string public name;
	uint public productCount = 0;
	mapping(uint => Product) public products;

	struct Product {
		uint id;
		string name;
		uint price;
		address payable owner;
		bool purchased;
	}

	event ProductCreated(
		uint id,
		string name,
		uint price,
		address  payable owner,
		bool purchased
	);

	event ProductPurchased(
		uint id,
		string name,
		uint price,
		address  payable owner,
		bool purchased
	);

	constructor() {
	    name = "Online parduotuve";
    }

	function createProduct(string memory _name, uint _price) public {
		// Require name
		require(bytes(_name).length > 0);
		// Require valid price
		require(_price > 0);
		// Increment product count
		productCount ++;
		// Create product
		products[productCount] = Product(productCount, _name, _price, payable(msg.sender), false);
		// Trigger event
		emit ProductCreated(productCount, _name, _price, payable (msg.sender), false);
	}

	function purchasedProduct(uint _id) public payable {
		// Fetch the product
		Product memory _product = products[_id];
		// Fetch the owner
		address payable _seller = _product.owner;
		// Product has valid id
		require(_product.id > 0 && _product.id <= productCount);
		//Enough ether in the transaction
		require(msg.value >= _product.price);
		//Product is not already purchased
		require(!_product.purchased);
		//Buyer is not the seller
		require(_seller != msg.sender);
		// Transfer ownership
		_product.owner = payable(msg.sender);
		// Mark it as purchased
		_product.purchased = true;
		// Update the prodocut
		products[_id] = _product;
		// Pay the seller
		payable(_seller).transfer(msg.value);
		// Trigger an even
		emit ProductPurchased(productCount, _product.name, _product.price, payable(msg.sender), true);

	}
}