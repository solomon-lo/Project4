// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#ifndef expandableHashMap
#define expandableHashMap


#include <string>
#include <functional>
#include <vector>


template<typename KeyType, typename ValueType>
class ExpandableHashMap
{
public:
	ExpandableHashMap(double maximumLoadFactor = 0.5);
	~ExpandableHashMap();
	void reset();
	int size() const;
	void associate(const KeyType& key, const ValueType& value);

	// for a map that can't be modified, return a pointer to const ValueType
	const ValueType* find(const KeyType& key) const;

	// for a modifiable map, return a pointer to modifiable ValueType
	ValueType* find(const KeyType& key)
	{
		return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
	}

	// C++11 syntax for preventing copying and assignment
	ExpandableHashMap(const ExpandableHashMap&) = delete;
	ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

	void deleteAllNodesInVectorOfNodes();

private:

	//NODE IMPLEMENTATION:
	struct Node
	{
	public:
		KeyType key;
		ValueType value;
		Node* nextNode;
	};


	std::vector<Node*> vectorOfNodes;
	int m_numOfAssociations;
	double currentLoadFactor;
};

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor)
{
	currentLoadFactor = maximumLoadFactor;
	for (int i = 0; i < 8; i++)
	{
		vectorOfNodes.push_back(nullptr);
	}

}

template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap()
{
	deleteAllNodesInVectorOfNodes();
	vectorOfNodes.clear();

}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::deleteAllNodesInVectorOfNodes()
{
	for (int i = 0; i < vectorOfNodes.size(); i++)
	{
		Node* tempNode = vectorOfNodes[i];
		while(tempNode->nextNode != nullptr)
		{
			Node* killMe = tempNode;
			tempNode = tempNode->nextNode;
			delete killMe;
		}
	}
}
template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reset()
{
	deleteAllNodesInVectorOfNodes();

	for(int i = 0; i < 8; i++)
	{
		vectorOfNodes.push_back(nullptr);
	}

}

template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const
{
	return vectorOfNodes.size();  
}


template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value)
{
	if (find(key) == nullptr)
	{
		//checks to see if it exceeds the loadfactor, and creates a new vector if it does
		if ((m_numOfAssociations + 1) > (vectorOfNodes.size() * currentLoadFactor))
		{
			std::vector<Node*> newHashVector;
			for (int i = 0; i < size() * 2; i++)
			{
				newHashVector.push_back(nullptr);
			}

			for (int i = 0; i < vectorOfNodes.size(); i++)
			{
				if (vectorOfNodes[i] != nullptr)
				{
					unsigned int hash(const KeyType & k, int numOfBuckets);
					int tempHash = hash(vectorOfNodes[i]->key, newHashVector.size());
					Node* insertNode = vectorOfNodes[i];
					while (vectorOfNodes[i] != nullptr)
					{
						Node* toInsertNode = vectorOfNodes[i];
						unsigned int hash(const KeyType & k, int numOfBuckets);
						int insertNodeTempHash = hash(vectorOfNodes[i]->key, newHashVector.size());
						toInsertNode->nextNode = newHashVector[insertNodeTempHash];
						newHashVector[insertNodeTempHash] = toInsertNode;
						vectorOfNodes[i] = vectorOfNodes[i]->nextNode;
					}
				}

			}
			vectorOfNodes = newHashVector;
		}

		unsigned int hash(const KeyType & k, int numOfBuckets);
		int insertBucketHash = hash(key, size());

		Node* insertNode = new Node;
		insertNode->key = key;
		insertNode->value = value;
		insertNode->nextNode = vectorOfNodes[insertBucketHash];

		vectorOfNodes[insertBucketHash] = insertNode;
		m_numOfAssociations++;
	}
	else
	{
		*find(key) = value;
	}
}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const	//TODO:CHANGE BACK TO "KeyType&" instead of "string"
{
	unsigned int hash(const KeyType & k, int numOfBuckets);
	unsigned int findIndex = hash(key, size());
	Node* tempNode = vectorOfNodes[findIndex];
	while (tempNode != nullptr)
	{
		if (tempNode->key == key)
		{
			return &tempNode->value;
		}
		else
		{
			tempNode = tempNode->nextNode;
		}
	}
	return nullptr;
}




#endif // !expandableHa