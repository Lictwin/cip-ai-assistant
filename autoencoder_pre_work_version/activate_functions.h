#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#define RIGHT_MATH

using std::pow;
using std::tanh;
using std::sin;
using std::cos;
using std::exp;
using std::log;
using std::fabs;
using std::asin;
using std::atanh;
using std::acos;

class AbstractActivator {
public:
	virtual double activate(double x) = 0;
	virtual double dif_activate(double x) = 0;
	virtual double dif_activate_per_activate(double y) = 0;
	virtual double inverse(double y, double dif_value = 0) = 0;
};

class Identical : public AbstractActivator {
public:
	virtual double activate(double x) {
		return x;
	}
	virtual double dif_activate(double x) {
		return 1;
	}
	virtual double dif_activate_per_activate(double y) {
		return 1;
	}
	virtual double inverse(double y, double dif_value = 0) {
		return y;
	}
};

class Linear : public AbstractActivator {
	double a;

public:
	virtual double activate(double x) {
		return a * x;
	};
	virtual double dif_activate(double x) {
		return a;
	};
	virtual double dif_activate_per_activate(double y) {
		return a;
	};
	virtual double inverse(double y, double dif_value = 0) {
		return y / a;
	}

	Linear(double a) {
		this->a = a;
	}
};

typedef Linear Lin;

class BiasLinear : public AbstractActivator {
	double a;
	double b;

public:
	virtual double activate(double x) {
		return a * x + b;
	}
	virtual double dif_activate(double x) {
		return a;
	}
	virtual double dif_activate_per_activate(double y) {
		return a;
	}
	virtual double inverse(double y, double dif_value = 0) {
		return (y - b) / a;
	}

	BiasLinear(double a, double b) {
		this->a = a;
		this->b = b;
	}
};

typedef BiasLinear BLin;

class ThresholdLinear : public AbstractActivator {
	double a;
	double b;

public:
	virtual double activate(double x) {
		return a * x - b;
	}
	virtual double dif_activate(double x) {
		return a;
	}
	virtual double dif_activate_per_activate(double y) {
		return a;
	}
	virtual double inverse(double y, double dif_value = 0) {
		return (y + b) / a;
	}

	ThresholdLinear(double a, double b) {
		this->a = a;
		this->b = b;
	}
};

typedef ThresholdLinear TLin;

class Logistic : public AbstractActivator {
public:
	virtual double activate(double x) override {
		return 1 / (1 + exp(-x));
	}
	virtual double dif_activate(double x) override {
		return exp(-x) / pow((1 + exp(-x)), 2);
	}
	virtual double dif_activate_per_activate(double y) {
		return y * (1 - y);
	}
	virtual double inverse(double y, double dif_value = 0) {
		return - log(1/y - 1);
	}
};

typedef Logistic Logist;

class BipolarLogistic : public AbstractActivator {
public:
	virtual double activate(double x) override {
		return 2 / (1 + exp(-x)) - 1;
	}
	virtual double dif_activate(double x) override {
		return 2 * exp(x) / pow((1 + exp(x)), 2);
	}
	virtual double dif_activate_per_activate(double y) {
		return 0.5 * y * (0 - y) + 0.5;
	}
	virtual double inverse(double y, double dif_value = 0) {
		return -log(2 / (y + 1) - 1);
	}
};

typedef BipolarLogistic BipolLogist;

class Sigmoid : public AbstractActivator {
	double a;

public:
	virtual double activate(double x) override {
		return 1 / (1 + exp(-a * x));
	}
	virtual double dif_activate(double x) override {
		return a * exp(-a * x) / pow((1 + exp(-a * x)), 2);
	}
	virtual double dif_activate_per_activate(double y) {
		return a * y * (1 - y);
	}
	virtual double inverse(double y, double dif_value = 0) {
		return (- log(1 / y - 1)) / a;
	}

	Sigmoid(double a) {
		this->a = a;
	}
};

typedef Sigmoid Sigm;

class BipolarSigmoid : public AbstractActivator {
	double a;

public:
	virtual double activate(double x) override {
		return 2 / (1 + exp(-a * x)) - 1;
	}
	virtual double dif_activate(double x) override {
		return 2 * a * exp(-a * x) / pow((1 + exp(-a * x)), 2);
	}
	virtual double dif_activate_per_activate(double y) {
		return 0.5 * a * y * (0 - y) + 0.5 * a;
	}
	virtual double inverse(double y, double dif_value = 0) {
		return (- log(2 / (y + 1) - 1)) / a;
	}

	BipolarSigmoid(double a) {
		this->a = a;
	}
};

typedef BipolarSigmoid BipolSigm;

class HyperbolicTangent : public AbstractActivator {
public:
	virtual double activate(double x) {
		return tanh(x);
	};
	virtual double dif_activate(double x) {
		return 1 / pow(cosh(x), 2);
	};
	virtual double dif_activate_per_activate(double y) {
		return 1 - pow(y, 2);
	};
	virtual double inverse(double y, double dif_value = 0) {
		return atanh(y);
	}
};

typedef HyperbolicTangent TypTan;
typedef HyperbolicTangent Th;

class SoftSign : public AbstractActivator {
public:
	virtual double activate(double x) {
		return x / (1 + fabs(x));
	}
	virtual double dif_activate(double x) {
		return 1 / pow((1 + fabs(x)), 2);
	}
	virtual double dif_activate_per_activate(double y) {
		if (y == 0)
			return 1;
		else 
			return pow(y, 2) / pow(this->inverse(y), 2);
	}
	virtual double inverse(double y, double dif_value = 0) {
		if (y <= 0)
			return y / (1 + y);
		else
			return y / (1 - y);
	}
};

class CleanSinus : public AbstractActivator {
public:
	virtual double activate(double x) {
		return sin(x);
	}
	virtual double dif_activate(double x) {
		return cos(x);
	}
	virtual double dif_activate_per_activate(double y) {
		return pow(1 - pow(y, 2), 0.5); 
	}
	virtual double inverse(double y, double dif_value = 0) {
		return asin(y); 
	}
};

typedef CleanSinus Sinus;
typedef CleanSinus Sin;

class LimitedSinus : public AbstractActivator {
public:
	virtual double activate(double x) {
		if (x >= M_PI / 2)
			return 1;
		else if (x <= M_PI / 2)
			return -1;
		else
			return cos(x);
	}
	virtual double dif_activate(double x) {
		if (x >= M_PI || x <= M_PI)
			return 0;
		else
			return -sin(x);
	}
	virtual double dif_activate_per_activate(double y) {
		if (y == 1 || y == -1)
			return 0;
		else 
			return -pow(1 - pow(y, 2), 0.5);
	}
	virtual double inverse(double y, double dif_value = -1) {
		double inverse_value = asin(y);
		if (dif_value > 0)
			inverse_value *= -1;
		return inverse_value;
	}
};

typedef LimitedSinus LSinus;
typedef LimitedSinus LSin;

class CleanCosinus : public AbstractActivator {
public:
	virtual double activate(double x) {
		return cos(x);
	}
	virtual double dif_activate(double x) {
		return -sin(x);
	}
	virtual double dif_activate_per_activate(double y) {
		return -pow(1 - pow(y, 2), 0.5);
	}
	virtual double inverse(double y, double dif_value = -1) {
		double inverse_value = acos(y);
		if (dif_value > 0)
			inverse_value *= -1;
		return inverse_value;
	}
};

typedef CleanCosinus Cosinus;
typedef CleanCosinus Cos;

class LimitedCosinus : public AbstractActivator {
public:
	virtual double activate(double x) {
		if (x >= M_PI || x <= M_PI)
			return -1;
		else 
			return cos(x);
	}
	virtual double dif_activate(double x) {
		if (x > M_PI || x < M_PI)
			return 0;
		else
			return -sin(x);
	}
	virtual double dif_activate_per_activate(double y) {
		return -pow(1 - pow(y, 2), 0.5);
	}
	virtual double inverse(double y, double dif_value = -1) {
		double inverse_value = acos(y);
		if (dif_value > 0)
			inverse_value *= -1;
		return inverse_value;
	}
};

typedef LimitedCosinus LCosinus;
typedef LimitedCosinus LCos;

class Sinc : public AbstractActivator {
public:
	virtual double activate(double x) {
		if (x == 0)
			return 1;
		else
			return sin(x) / x;
	}
	virtual double dif_activate(double x) {
		if (x == 0)
			return 0;
		else
			return cos(x) / x - sin(x) / pow(x, 2);
	}
	virtual double dif_activate_per_activate(double y) {
		return -1; // TODO
	}
	virtual double inverse(double y, double dif_value = 0) {
		if (y == 1)
			return 0;
		else
			return -1; // TODO
	}
};

class Gaussian : public AbstractActivator {
public:
	virtual double activate(double x) {
		return exp(-pow(x,2));
	}
	virtual double dif_activate(double x) {
		return 2 * x * this->activate(x);
	}
	virtual double dif_activate_per_activate(double y) {
		return 2 * y * this->inverse(y); 
	}
	virtual double inverse(double y, double dif_value = 1) {
		double inverse_value = pow(-log(y), 0.5);
		if (dif_value < 0)
			inverse_value *= -1;
		return inverse_value;
	}
};