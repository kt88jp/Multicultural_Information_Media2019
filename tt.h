#pragma once
#include <limits>
#include <cstring>
#include <stdint.h>
#include <iostream>
// �u���\�Ɋւ���R�[�h

// �����ݒ肵�Ă����ƁA�u���\�Ɋւ���l�X�ȃJ�E���g�f�[�^���L�^����悤�ɂȂ�
#define TT_COUNT

// �u���\�̃L�[�̌^�B64�r�b�g�Ƃ���
using Key = uint64_t;

// �u���\�ɋL�^����f�[�^�i2��n��̃r�b�g���ɂ���j
//struct TT_DATA {
//	// �L�[�i63�r�b�g�i���1�r�b�g�������j�j
//	// ���1�r�b�g�������Ă���Ƃ��A����63�r�b�g�̃L�[�͂��łɒT���ςł��邱�Ƃ�\��
//	Key			key;
//
//	bool isset() const {
//		return key & 0x8000000000000000;
//	}
//
//	bool operator==(const Key& k) const
//	{
//		return (key & 0x7fffffffffffffff) == (k & 0x7fffffffffffffff);
//	};
//
//	void set(const Key& k) {
//		key = k | 0x8000000000000000;
//	}
//};

//struct TT_DATA {
//	// �L�[�i56�r�b�g�i���8�r�b�g�������j�j
//	// ���8�r�b�g��0�łȂ����A�c���56�r�b�g�̃L�[�͂��łɒT���ςł��邱�Ƃ�\��
//	Key			key;
//
//	bool isset() const {
//		return key & static_cast<uint64_t>(0x00000000000000ff);
//	}
//
//	bool operator==(const Key& k) const
//	{
//		return (key & 0xffffffffffffff00) == (k & 0xffffffffffffff00);
//	};
//
//	void set(const Key& k, const uint8_t value) {
//		key = (k & 0xffffffffffffff00) | static_cast<uint64_t>(value); // 0x00000000000000ff;
//	}
//	uint8_t get() const {
//		return static_cast<uint8_t>(key & static_cast<uint64_t>(0xff));
//	}
//};

struct TT_DATA {
	// �L�[�i56�r�b�g�i���8�r�b�g�������j�j
	// ���8�r�b�g��0�łȂ����A�c���56�r�b�g�̃L�[�͂��łɒT���ςł��邱�Ƃ�\��
	Key			key;
	double		data;

	bool isset() const {
		return data != 0;
	}

	bool operator==(const Key& k) const
	{
		return key == k;
	};

	void set(const Key& k, const double value) {
		key = k;
		data = value;
	}
	double get() const {
		return data;
	}
};


// �u���\�̃n�b�V���̃r�b�g��-1
// �L���b�V���̊֌W��A15�����肪�ő����ۂ��H
constexpr int TT_HASH_BIT = 16;
// �N���X�^�[�̐�
constexpr int TT_CLUSTERCOUNT = 1 << TT_HASH_BIT;
// �N���X�^�[�̃T�C�Y
constexpr int TT_CLUSTERSIZE = 4;
struct TT_CLUSTER {
	TT_DATA data[TT_CLUSTERSIZE];
};

struct alignas(32) TT_TABLE {
	TT_CLUSTER table[TT_CLUSTERCOUNT];
#ifdef TT_COUNT
	// ���̒u���\�Ɋւ���l�X�ȃJ�E���g���s�����߂̕ϐ�
	int hitcount, nothitcount, conflictcount, dropcount;
	int totalhitcount, totalnothitcount, totalconflictcount, totaldropcount;
#endif
	// key �Ɉ�v����L���b�V��������΂����Ԃ�
	TT_DATA* findcache(const Key key, bool& found) {
		TT_CLUSTER* c = &table[key & (TT_CLUSTERCOUNT - 1)];
		for (int i = 0; i < TT_CLUSTERSIZE; i++) {
			// �o�^�ς��ǂ����𔻒肷��
			if (!c->data[i].isset()) {
				found = false;
#ifdef TT_COUNT
				nothitcount++;
				totalnothitcount++;
#endif
				return &c->data[i];
			}
			// �o�^�ς̏ꍇ�Akey�̔�����s��
			if (c->data[i] == key) {
				found = true;
#ifdef TT_COUNT
				hitcount++;
				totalhitcount++;
				if (i > 0) {
					conflictcount++;
					totalconflictcount++;
				}
#endif
				return &c->data[i];
			}
		}
		found = false;
		for (int i = TT_CLUSTERSIZE - 1; i > 0; i--) {
			c->data[i] = c->data[i - 1];
		}
#ifdef TT_COUNT
		dropcount++;
		totaldropcount++;
		nothitcount++;
		totalnothitcount++;
		conflictcount++;
		totalconflictcount++;
#endif
		return &c->data[0];
	}
#ifdef TT_COUNT
	TT_TABLE() : totalhitcount(0), totalnothitcount(0), totalconflictcount(0), totaldropcount(0) {
#else
	TT_TABLE() {
#endif
		clear();
	}
	void clear() {
#ifdef TT_COUNT
		hitcount = 0;
		nothitcount = 0;
		dropcount = 0;
		conflictcount = 0;
#endif
		memset(&table[0], 0, sizeof(TT_CLUSTER) * TT_CLUSTERCOUNT);
	}
#ifdef TT_COUNT
	void dump_count() const {
		std::cerr << "hit " << hitcount << " nothit " << nothitcount << " confilct " << conflictcount << " drop " << dropcount << std::endl;
	}
	void dump_totalcount() const {
		std::cerr << "total hit " << totalhitcount << " nothit " << totalnothitcount << " confilct " << totalconflictcount << " drop " << totaldropcount << std::endl;
	}
#else
	void dump_count() const {}
	void dump_totalcount() const {}
#endif
	};